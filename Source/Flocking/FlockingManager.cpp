#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 20
#define MAX_SPEED 2000.f
#define BOUNDARY_RADIUS 5000

void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh, AMyCharacter* character  ) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));

    Character = character;
    
    World = world;
    if( World != nullptr ) {

        // Point generation algorithm adapted from:
        // http://extremelearning.com.au/evenly-distributing-points-on-a-sphere/
            
        for( int i = 0; i < AGENT_COUNT; i++ ) {
            FVector2D flatPoint = FMath::RandPointInCircle(BOUNDARY_RADIUS);

            FVector location = FVector(flatPoint, 0.f);

            AAgent* agent = World->SpawnActor<AAgent>(location, FRotator());
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
// Pseudo code retrieved from http://www.kfish.org/boids/pseudocode.html

		for(auto boid : Agents) {
			auto v1 = rule1(boid);
			auto v2 = rule2(boid);
			auto v3 = rule3(boid);
      auto v4 = boundPosition(boid);
      auto v5 = tendToPlace(boid);

			boid->Velocity += v1 + v2 + v3 + v4 + v5;
      boid->Velocity = boid->Velocity.GetClampedToMaxSize(MAX_SPEED);
      boid->Velocity.Z = 0.f;
    }
}

// Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
FVector UFlockingManager::rule1(AAgent* focusBoid) {
    FVector centersTotal;

    for(auto boid : Agents) {
      if(boid != focusBoid) {
        centersTotal += boid->GetActorLocation();
      }
    }

    FVector averageCenter = centersTotal / (AGENT_COUNT-1);

    return (averageCenter - focusBoid->GetActorLocation()) / 50;
}

// Rule 2: Boids try to keep a small distance away from other objects (including other boids).
FVector UFlockingManager::rule2(AAgent* focusBoid) {
    FVector vec;

    for(auto boid : Agents) {
      float distance = FVector::Distance(boid->GetActorLocation(), focusBoid->GetActorLocation());

      int repulsiveRadius = 500;
      if((boid != focusBoid) && (distance < repulsiveRadius)) {
        vec -= (boid->GetActorLocation() - focusBoid->GetActorLocation()) * repulsiveRadius * repulsiveRadius / (distance * distance * 10);
      }
    }

    return vec;
}

// Rule 3: Boids try to match velocity with near boids.
FVector UFlockingManager::rule3(AAgent* focusBoid) {
    FVector velocitiesTotal;

    for(auto boid : Agents) {
      if(boid != focusBoid) {
        velocitiesTotal += boid->Velocity;
      }
    }

    FVector averageVelocity = velocitiesTotal / (AGENT_COUNT-1);

    return (averageVelocity - focusBoid->Velocity) / 8;
}

FVector UFlockingManager::boundPosition(AAgent* focusBoid) {
    FVector vec;
    
    FVector location = focusBoid->GetActorLocation();

    if(location.Size() > BOUNDARY_RADIUS) {
      vec = (location.GetSafeNormal() * BOUNDARY_RADIUS) - location;
    }

    return vec;
}

FVector UFlockingManager::tendToPlace(AAgent* focusBoid) {
    FVector place = Character->GetActorLocation();

    FVector vec = (place - focusBoid->GetActorLocation()) / 25;

    return vec.GetClampedToMaxSize(3000.f);
}
#include "FlockingGameModeBase.h"

AFlockingGameModeBase::AFlockingGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AFlockingGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));

    Character = NewObject<AMyCharacter>();

    Manager = NewObject<UFlockingManager>();
    Manager->Init( GetWorld(), AgentMesh, Character );
}

void AFlockingGameModeBase::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    Manager->Flock();
};
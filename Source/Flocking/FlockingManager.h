#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init( UWorld *world, UStaticMeshComponent *mesh, AMyCharacter* character );
	void Flock();

private:
	UWorld *World;	
	bool initialized;
	TArray<class AAgent *> Agents;
	AMyCharacter* Character;

	FVector rule1(AAgent* focusBoid);
	FVector rule2(AAgent* focusBoid);
	FVector rule3(AAgent* focusBoid);
	FVector boundPosition(AAgent* focusBoid);
	FVector tendToPlace(AAgent* focusBoid);
};
// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "MyCharacter.h"
#include "FlockingGameModeBase.generated.h"

UCLASS()
class FLOCKING_API AFlockingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AFlockingGameModeBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent * AgentMesh;

	UPROPERTY() UFlockingManager *Manager;
	UPROPERTY() AMyCharacter *Character;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
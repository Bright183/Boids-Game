// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 3000.f;
    UE_LOG(LogTemp, Warning, TEXT("Character Constructed"));

}

void AMyCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if( !GetActorRotation().IsZero() ) {
		UE_LOG(LogTemp, Warning, TEXT("Collision") );
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AMyCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
}

void AMyCharacter::MoveUp(float AxisVal)
{
	AddMovementInput(GetActorForwardVector()* AxisVal);
}

void AMyCharacter::MoveRight(float AxisVal)
{
	AddMovementInput(GetActorRightVector()* AxisVal);
}





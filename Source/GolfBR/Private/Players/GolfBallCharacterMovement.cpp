// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/GolfBallCharacterMovement.h"
#include "GameFramework/Character.h"
#include "Engine/UserDefinedEnum.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Players/CustomMovementMode.h"


UGolfBallCharacterMovement::UGolfBallCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

}

void UGolfBallCharacterMovement::BeginPlay() {
	Super::BeginPlay();
	//VictoryEnum = EVictory::VE_Dance;

	//UTextUtil::GetEnumValueAsString<EnumClassName>(FString(TEXT(EVictory)), (ValueOfEnum))

	VictoryEnum = EVictory::VE_Dance;
	//FString EnumString = EnumToString(EVictory, EVictory::VE_Dance);


	//FString EnumString = EnumToString(VictoryEnum, EVictoryEnum::VE_Dance);


/*
void UGolfBallCharacterMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &UGolfBallCharacterMovement::Jump);
	*/
}

void UGolfBallCharacterMovement::Jump(float deltatime, int32 Iterations) {

}

void UGolfBallCharacterMovement::PhysCustom(float deltaTime, int32 Iterations) {
	Jump(1.0f, 1);
	switch (VictoryEnum)
	{
	case EVictory::VE_Dance:
		Jump(1.0f, 1);
		break;
	default:
		break;
	}
}




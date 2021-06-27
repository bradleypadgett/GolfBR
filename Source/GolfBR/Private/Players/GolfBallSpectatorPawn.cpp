// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallSpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

AGolfBallSpectatorPawn::AGolfBallSpectatorPawn() {
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AGolfBallSpectatorPawn::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	SetTargetArmLength();
}


void AGolfBallSpectatorPawn::SetTargetArmLength() {

	float CameraPitch = FollowCamera->GetComponentRotation().Pitch * -1;
	float NormalizedPitch = UKismetMathLibrary::NormalizeToRange(CameraPitch, 5, 40);
	float ClampedPitch = UKismetMathLibrary::FClamp(NormalizedPitch, 0, 1);

	//UE_LOG(LogTemp, Warning, TEXT("Pitch: %f, PitchAdjust: %f, ClampedPitch: %f), CameraPitch, NormalizedPitch, ClampedPitch);

	CameraBoom->TargetArmLength = UKismetMathLibrary::Lerp(125, 250, ClampedPitch);
}
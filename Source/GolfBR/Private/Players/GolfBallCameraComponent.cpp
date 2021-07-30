// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallCameraComponent.h"
#include "Players/GolfBallPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Net/UnrealNetwork.h"
#include "Players/GolfBallMovementComponent.h"



// Sets default values for this component's properties
UGolfBallCameraComponent::UGolfBallCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

}


// Called when the game starts
void UGolfBallCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AGolfBallPlayer>(GetOwner());
	Camera = Owner->GetCamera();
	CameraBoom = Owner->GetCameraBoom();
	ArrowCenter = Owner->GetArrowCenter();
	Arrow = Owner->GetArrow();
	MovementComponent = Owner->GetMoveComponent();

	//sets rotation to absolute so the arrow doesn't go brr with ball
	ArrowCenter->SetAbsolute(false, true, false);


	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->ViewPitchMin = MinPitch;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->ViewPitchMax = MaxPitch;

}

void UGolfBallCameraComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Here we list the variables we want to replicate + a condition if wanted
	DOREPLIFETIME(UGolfBallCameraComponent, ReplicatedArrowTargetRotation);
}

// Called every frame
void UGolfBallCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SetTargetArmLength();
	UpdateArrowRotation(DeltaTime);
}

void UGolfBallCameraComponent::SetTargetArmLength() {

	float CameraPitch = Camera->GetComponentRotation().Pitch * -1;
	float NormalizedPitch = UKismetMathLibrary::NormalizeToRange(CameraPitch, 5, 40);
	float ClampedPitch = UKismetMathLibrary::FClamp(NormalizedPitch, 0, 1);

	//UE_LOG(LogTemp, Warning, TEXT("Pitch: %f, PitchAdjust: %f, ClampedPitch: %f), CameraPitch, NormalizedPitch, ClampedPitch);

	CameraBoom->TargetArmLength = UKismetMathLibrary::Lerp(125, 250, ClampedPitch);
}

//called from everyone from tick. Updates Arrow Rotation
void UGolfBallCameraComponent::UpdateArrowRotation(float DeltaTime) {

	// If it's the client then it'll call the server and replicate
	if (GetOwnerRole() == ROLE_AutonomousProxy && !Owner->Testing) {

		FRotator Rotation = UKismetMathLibrary::MakeRotFromX(MovementComponent->CalculateShotDirection(false));

		FRotator TargetRotation = UKismetMathLibrary::RInterpTo(ArrowCenter->GetComponentRotation(), Rotation, DeltaTime, 10);

		Server_UpdateArrowRotation(DeltaTime, TargetRotation.Quaternion());
		ArrowCenter->SetWorldRotation(TargetRotation.Quaternion());
	}
	else if (!Owner->Testing) {
		//UE_LOG(LogTemp, Warning, TEXT("MyRotation: %s"), *ReplicatedArrowTargetRotation.ToString());
		ArrowCenter->SetWorldRotation(ReplicatedArrowTargetRotation);
	}

	if (Owner->Testing) {
		FRotator Rotation = UKismetMathLibrary::MakeRotFromX(MovementComponent->CalculateShotDirection(false));
		FRotator TargetRotation = UKismetMathLibrary::RInterpTo(ArrowCenter->GetComponentRotation(), Rotation, DeltaTime, 10);
		ArrowCenter->SetWorldRotation(TargetRotation.Quaternion());
	}

	//UE_LOG(LogTemp, Error, TEXT("%s"), *ReplicatedArrowTargetRotation.ToString());

}

void UGolfBallCameraComponent::Server_UpdateArrowRotation_Implementation(float DeltaTime, FQuat TargetRotation) {
	//UE_LOG(LogTemp, Error, TEXT("TargetRotation: %s"), *TargetRotation.ToString());

	ReplicatedArrowTargetRotation = TargetRotation;

}

bool UGolfBallCameraComponent::Server_UpdateArrowRotation_Validate(float DeltaTime, FQuat TargetRotation) {
	return true;
}

void UGolfBallCameraComponent::TurnAtRate(float Rate) {
	// calculate delta for this frame from the rate information
	Owner->AddControllerYawInput(Rate * BaseTurnRate * Owner->GetWorld()->GetDeltaSeconds());
}

void UGolfBallCameraComponent::Turn(float Rate) {
	Owner->AddControllerYawInput(Rate);
}

void UGolfBallCameraComponent::LookUpAtRate(float Rate) {
	// calculate delta for this frame from the rate information
	Owner->AddControllerPitchInput(Rate * BaseLookUpRate * Owner->GetWorld()->GetDeltaSeconds());
}

void UGolfBallCameraComponent::LookUp(float Rate) {
	Owner->AddControllerPitchInput(Rate);
}
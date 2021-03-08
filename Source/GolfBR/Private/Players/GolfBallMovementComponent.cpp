// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallMovementComponent.h"
#include "Players/GolfBallPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UGolfBallMovementComponent::UGolfBallMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UGolfBallMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AGolfBallPlayer>(GetOwner());
	GolfBall = Owner->GetGolfBall();
	FollowCamera = Owner->GetCamera();

}

void UGolfBallMovementComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGolfBallMovementComponent, ReplicatedTransform);
	DOREPLIFETIME(UGolfBallMovementComponent, BallReplicatedTransform);
	DOREPLIFETIME(UGolfBallMovementComponent, ReplicatedLinearVelocity);
	DOREPLIFETIME(UGolfBallMovementComponent, ReplicatedAngularVelocity);
	DOREPLIFETIME(UGolfBallMovementComponent, Velocity);

}

// Called every frame
void UGolfBallMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwnerRole() == ROLE_Authority) {
		ReplicatedTransform = Owner->GetActorTransform();
		//Velocity = Owner->GetVelocity();
		BallReplicatedTransform = GolfBall->GetComponentTransform();
		ReplicatedLinearVelocity = GolfBall->GetPhysicsLinearVelocity();
		ReplicatedAngularVelocity = GolfBall->GetPhysicsAngularVelocityInDegrees();
		DampenMovement();

	}
	else {
		GolfBall->SetPhysicsLinearVelocity(ReplicatedLinearVelocity);
		GolfBall->SetPhysicsAngularVelocityInDegrees(ReplicatedAngularVelocity);
		DampenMovement();
	}

}

void UGolfBallMovementComponent::OnRep_ReplicatedTransform() {
	if (Owner && GolfBall && GetOwnerRole() != ROLE_Authority) {
	//Owner->SetActorTransform(ReplicatedTransform);
	Owner->SetActorLocation(ReplicatedTransform.GetLocation());
	GolfBall->SetWorldTransform(BallReplicatedTransform);
	}
}

bool UGolfBallMovementComponent::IsOnGround() {

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Owner->GetActorLocation(), (Owner->GetActorLocation() - FVector(0, 0, 20)), ECC_Visibility);
	return Hit.bBlockingHit;
}



//Gets called when you press shoot button
void UGolfBallMovementComponent::ChargeShotSetup()
{
	Charging = true;
	Dashing = true;
	FTimerHandle DashDelay;
	//sets a delay to dash if you release within .25 seconds
	GetWorld()->GetTimerManager().SetTimer(DashDelay, this, &UGolfBallMovementComponent::DisableDashStartCharge, 1.0f, false, .25f);
	GetWorld()->GetTimerManager().SetTimer(ChargeShotHandle, this, &UGolfBallMovementComponent::ChargeShot, .015f, true, .25f);
}

void UGolfBallMovementComponent::ChargeShot() {
	FVector GolfBallSpeedVector = GolfBall->GetPhysicsLinearVelocity();
	GolfBallSpeedVector.Z = 0;
	float GolfBallSpeed = UKismetMathLibrary::VSize(GolfBallSpeedVector);

	if (Charge < 100 && GolfBallSpeed < 1) {
		Charge += 1;
	}
}



FVector UGolfBallMovementComponent::CalculateShotDirection(bool Turn90) {
	FVector GlobalAxisImpulse = UKismetMathLibrary::MakeVector(Owner->GetInputAxisValue("MoveForward"), Owner->GetInputAxisValue("MoveRight"), 0.f);
	
	bool bLocalImpulseIsZero = UKismetMathLibrary::EqualEqual_VectorVector(FVector(0, 0, 0), GlobalAxisImpulse, KINDA_SMALL_NUMBER);
	GlobalAxisImpulse = UKismetMathLibrary::SelectVector(FVector(1, 0, 0), GlobalAxisImpulse, bLocalImpulseIsZero);

	float Offset = Turn90 ? 90 : 0;
	float GlobalToLocalRotation = FollowCamera->GetComponentRotation().Yaw + Offset;

	return GlobalAxisImpulse.RotateAngleAxis(GlobalToLocalRotation, FVector(0, 0, 1));
}

void UGolfBallMovementComponent::Jump() {
	if (GetOwnerRole() != ROLE_Authority) {
	GolfBall->AddImpulse(FVector(0, 0, JumpHeight * 100));
	}
	Server_Jump();
}

void UGolfBallMovementComponent::Server_Jump_Implementation() {
	if (!IsOnGround()) { return; }
	GolfBall->AddImpulse(FVector(0, 0, JumpHeight * 25));
}

bool UGolfBallMovementComponent::Server_Jump_Validate() {
	return true;
}

void UGolfBallMovementComponent::ShootBall() {
	FVector GolfBallSpeedVector = GolfBall->GetPhysicsLinearVelocity();
	GolfBallSpeedVector.Z = 0;
	float GolfBallSpeed = UKismetMathLibrary::VSize(GolfBallSpeedVector);

	if ((!Dashing && Charge > 0 && GolfBallSpeed < 5) || DashCooldown == 0 && Dashing) {
		//sets velocity to 0 only if you're doing a normal shot OR you can dash
		float ImpulseMultiplier = (Dashing && CanDash) ? DashSpeed * 10 : Charge * MaxCharge / 10;
		FVector Impulse = ImpulseMultiplier * CalculateShotDirection(false);
		FVector RadialImpulse = ImpulseMultiplier * 100000 * CalculateShotDirection(true);

		if (GetOwnerRole() != ROLE_Authority) {
			GolfBall->SetAllPhysicsLinearVelocity(FVector(0, 0, GolfBall->GetComponentVelocity().Z));
			GolfBall->AddImpulse(Impulse, "", true);
			GolfBall->AddTorqueInDegrees(RadialImpulse, "", true);
		}

		Server_ShootBall(Impulse, RadialImpulse);
	}
	//handles if you dash
	if (Dashing && DashCooldown == 0) {

		DashCooldown = 100;
		GetWorld()->GetTimerManager().SetTimer(DashDelayHandle, this, &UGolfBallMovementComponent::UpdateDashCooldown, (10.f * .01f), true, 0.f);
	}

	Charging = false;
	GetWorld()->GetTimerManager().PauseTimer(ChargeShotHandle);
	Charge = 0;

}

void UGolfBallMovementComponent::Server_ShootBall_Implementation(FVector Impulse, FVector RadialImpulse)
{
	GolfBall->SetAllPhysicsLinearVelocity(FVector(0, 0, GolfBall->GetComponentVelocity().Z));
	GolfBall->AddImpulse(Impulse, "", true);
	GolfBall->AddTorqueInDegrees(RadialImpulse, "", true);
}

bool UGolfBallMovementComponent::Server_ShootBall_Validate(FVector Impulse, FVector RadialImpulse) {
	return true;
}


void UGolfBallMovementComponent::UpdateDashCooldown() {
	if (DashCooldown > 0) {
		DashCooldown -= 1;
	}
	else {
		GetWorld()->GetTimerManager().PauseTimer(DashDelayHandle);
		DashCooldown = 0;
	}
}

void UGolfBallMovementComponent::DampenMovement() {
	float Speed = UKismetMathLibrary::VSize(GolfBall->GetPhysicsLinearVelocity());
	FVector LinearVelocity = GolfBall->GetPhysicsLinearVelocity();
	FVector AngularVelocity = GolfBall->GetPhysicsAngularVelocityInDegrees();

	//UE_LOG(LogTemp, Error, TEXT("%f"), Speed);
	if (UKismetMathLibrary::InRange_FloatFloat(Speed, 10.f, DampenStartSpeed, true, true)) {
		FVector Direction = GolfBall->GetPhysicsLinearVelocity();
		Direction.Normalize(KINDA_SMALL_NUMBER);

		//UE_LOG(LogTemp, Warning, TEXT("%s is ACTUALLY dampening"), *Owner->GetName());


		GolfBall->AddForce(FVector(Direction.X * -(DampenStrength), Direction.Y * -(DampenStrength), 0), NAME_None, true);

		}
	else if (!IsOnGround() && Speed > 10.f) {
		FVector Direction = GolfBall->GetPhysicsLinearVelocity();
		Direction.Normalize(KINDA_SMALL_NUMBER);

		GolfBall->AddForce(FVector(Direction.X*-(DampenStrength+100), Direction.Y*-(DampenStrength+100), 0), NAME_None, true);
	}
	else if (Speed <= 10.f && IsOnGround()) {
		GolfBall->SetPhysicsLinearVelocity(FVector(LinearVelocity.X*.9, LinearVelocity.Y*.9, LinearVelocity.Z), false);
		GolfBall->SetPhysicsAngularVelocityInDegrees(FVector(AngularVelocity.X*.9, AngularVelocity.Y*.9, AngularVelocity.Z), false);
	}

}

void UGolfBallMovementComponent::MoveForward(float Value) { }

void UGolfBallMovementComponent::MoveRight(float Value) { }


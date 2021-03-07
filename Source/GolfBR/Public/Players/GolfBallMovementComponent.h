// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GolfBallPlayer.h"
#include "GolfBallMovementComponent.generated.h"

class AGolfBallPlayer;
class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOLFBR_API UGolfBallMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGolfBallMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 JumpHeight = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 DashSpeed = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 MaxCharge = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DampenStrength = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 DampenStartSpeed = 250;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Charge = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DashCooldown = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Dashing = false;
	UPROPERTY()
	FTimerHandle ChargeShotHandle;
	UPROPERTY()
	FTimerHandle DashDelayHandle;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
	FTransform ReplicatedTransform;
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
	FTransform BallReplicatedTransform;
	UPROPERTY(Replicated)
	FVector ReplicatedLinearVelocity;
	UPROPERTY(Replicated)
	FVector ReplicatedAngularVelocity;
	UPROPERTY(Replicated)
	FVector Velocity;

	UFUNCTION()
	void OnRep_ReplicatedTransform();

	bool CanDash = true;
	bool Charging;

	bool IsOnGround();

	void UpdateDashCooldown();

	void DisableDashStartCharge() { Dashing = false; }

	void DampenMovement();



private:
	
	UPROPERTY()
	AGolfBallPlayer* Owner;
	UPROPERTY()
	UStaticMeshComponent* GolfBall;
	UPROPERTY()
	UCameraComponent* FollowCamera;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Golf")
	FVector CalculateShotDirection(bool Turn90);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Jump();
	void Jump();

	void ChargeShot();
	void ChargeShotSetup();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ShootBall(FVector Impulse, FVector RadialImpulse);
	void ShootBall();

	void MoveForward(float Value);
	void MoveRight(float Value);
};
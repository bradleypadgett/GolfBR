// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GolfBallPlayer.h"
#include "UObject/ObjectMacros.h"
#include "GolfBallMovementComponent.generated.h"

class AGolfBallPlayer;
class UStaticMeshComponent;

// struct to get unique actions from autonomous proxy
// unique moves (dash/putt + direction) and deltatime 'cause fps might be different, etc
USTRUCT()
struct FGolfBallMove {

	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;

};

USTRUCT()
struct FGolfBallState {

	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FGolfBallMove LastMove;

	UPROPERTY()
	FVector LinearVelocity;
	UPROPERTY()
	FVector AngularVelocity;
	UPROPERTY()
	FTransform Transform;
};


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ChargeTimeMax = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* ShotSound;

	UPROPERTY(Replicated)
	bool bGainingSpeed = false;
	UPROPERTY(Replicated)
	float PreviousSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Charge = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DashCooldown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashCooldownTime = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bOnlyMoveWhenStopped = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bResetSpeedOnShot = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Dashing = false;
	UPROPERTY()
	FTimerHandle ChargeShotHandle;
	UPROPERTY()
	FTimerHandle DashDelayHandle;

	/*
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
	Transform ReplicatedTransform;
	/*UPROPERTY(Replicated)
	FVector ReplicatedLinearVelocity;
	UPROPERTY(Replicated)
	FVector ReplicatedAngularVelocity;
	UPROPERTY(Replicated)
	*/

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


	FVector LinearVelocity;
	FVector AngularVelocity;

	float ClientTimeSinceUpdate;
	float ClientTimeBetweenLastUpdates;

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
	FGolfBallState ServerState;

	UFUNCTION()
	void OnRep_ServerState();
	void AutonomousProxy_OnRep_ServerState();
	void SimulatedProxy_OnRep_ServerState();
	FVector ClientStartLocation;


	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_Move();

	void MoveForward(float Value);
	void MoveRight(float Value);
};

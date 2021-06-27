// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GolfBallPlayer.generated.h"

class UGolfBallCameraComponent;
class UGolfBallMovementComponent;
class UGolfBallReplicationComponent;

UCLASS()
class GOLFBR_API AGolfBallPlayer : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GolfBall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UGolfBallCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrow, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ArrowCenter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrow, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UGolfBallMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UGolfBallReplicationComponent* ReplicationComponent;

	UPROPERTY()
	APlayerCameraManager* CameraManager;


public:
	// Sets default values for this pawn's properties
	AGolfBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// input functions

	void TurnAtRate(float Rate);
	void Turn(float Rate);
	void LookUpAtRate(float Rate);
	void LookUp(float Rate);

	void ChargeShotSetup();
	void ShootBall();

public:
	// Called every frame
		virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getters
	UCameraComponent* GetCamera() { return FollowCamera; }
	USpringArmComponent* GetCameraBoom() { return CameraBoom; }
	USceneComponent* GetArrowCenter() { return ArrowCenter; }
	UArrowComponent* GetArrow() { return Arrow; }
	UStaticMeshComponent* GetGolfBall() { return GolfBall; }
	UGolfBallMovementComponent* GetMoveComponent() { return MovementComponent; }
	UGolfBallReplicationComponent* GetReplicationComponent() { return ReplicationComponent; }
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GolfBallCameraComponent.generated.h"

class AGolfBallPlayer;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class USceneComponent;
class UGolfBallMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOLFBR_API UGolfBallCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGolfBallCameraComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int32 MaxPitch = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int32 MinPitch = -75;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UPROPERTY()
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UPROPERTY()
	float BaseLookUpRate;

private:

	UPROPERTY()
	AGolfBallPlayer* Owner;
	UPROPERTY()
	UCameraComponent* Camera;
	UPROPERTY()
	USpringArmComponent* CameraBoom;
	UPROPERTY()
	UArrowComponent* Arrow;
	UPROPERTY()
	USceneComponent* ArrowCenter;
	UPROPERTY()
	UGolfBallMovementComponent* MovementComponent;

	void SetTargetArmLength();
	void UpdateArrowRotation(float DeltaTime);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TurnAtRate(float Rate);
	void Turn(float Rate);
	void LookUpAtRate(float Rate);
	void LookUp(float Rate);


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GolfBallSpectatorPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class GOLFBR_API AGolfBallSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:

	AGolfBallSpectatorPawn();

	virtual void Tick(float DeltaTime) override;

protected:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int32 MaxPitch = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int32 MinPitch = -75;

	void SetTargetArmLength();

};

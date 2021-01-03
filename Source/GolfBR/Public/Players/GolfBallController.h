// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GolfBallController.generated.h"

/**
 * 
 */
UCLASS()
class GOLFBR_API AGolfBallController : public APlayerController
{
	GENERATED_BODY()

public:
	AGolfBallController();

//	UFUNCTION()
	void Jump();

protected:
	// APawn interface
	virtual void SetupInputComponent() override;
	// End of APawn interface

	virtual void BeginPlay() override;

	//UPROPERTY()
	//UStaticMeshComponent* GolfBall;

};

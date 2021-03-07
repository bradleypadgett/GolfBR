// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Players/CustomMovementMode.h"
#include "GolfBallCharacterMovement.generated.h"

/**
 * 
 */

UCLASS()
class GOLFBR_API UGolfBallCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()
	
protected: 

	virtual void BeginPlay() override;

	virtual void PhysCustom(float Deltatime, int32 Iterations) override;

	void Jump(float deltatime, int32 Iterations);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EVictory VictoryEnum;

};

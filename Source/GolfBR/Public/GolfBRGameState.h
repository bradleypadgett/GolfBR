// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GolfBRGameState.generated.h"

/**
 * 
 */
UCLASS()
class GOLFBR_API AGolfBRGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
		FString LatestEvent;

	UPROPERTY(Replicated)
		FString WinningTeam;
};

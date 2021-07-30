// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GS_GolfBR.generated.h"

/**
 * 
 */
UCLASS()
class GOLFBR_API AGS_GolfBR : public AGameState
{
	GENERATED_BODY()
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = Lobby)
	void GetPlayers(TArray<APlayerState*>& Players);
};

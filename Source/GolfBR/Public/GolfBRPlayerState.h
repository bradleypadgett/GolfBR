// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GolfBRPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GOLFBR_API AGolfBRPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void PostInitializeComponents() override;

	virtual void CopyProperties(APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable)
	void SetPlayerNameExposed(FString Name);

	UPROPERTY()
		FString PlayerSessionId;

	UPROPERTY()
		FString MatchmakingPlayerId;

	UPROPERTY(Replicated)
		FString Team;
};

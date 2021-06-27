// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Players/GolfBallCharacter.h"
#include "Kismet/GameplayStatics.h"
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


	virtual void OnRep_Pawn() override;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	ASpectatorPawn* Spectator;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "State")
	APawn* OldPawn;

	UFUNCTION(BlueprintCallable, Category = "State")
	void ChangeState_To_Spectator();

	UFUNCTION(BlueprintCallable, Category = "State")
	void PossessSpectator(ASpectatorPawn* SpawnedSpectator);

	UFUNCTION(BlueprintCallable, Category = "State")
	void PossessPlayer();

	UFUNCTION(BlueprintCallable, Category = "State")
	void ChangeState_To_Player();

	UFUNCTION(BlueprintCallable, Category = "Start Spectating Player Controller")
		void StartSpectating();

	UFUNCTION(Client, Reliable)
		void Client_StartSpectating();

	UFUNCTION(BlueprintCallable, Category = "Start Spectating Player Controller")
		void StartPlaying();

protected:
	// APawn interface
	virtual void SetupInputComponent() override;
	// End of APawn interface

	virtual void BeginPlay() override;
	
	virtual void PreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel) override;

	UGameplayStatics* myStatics;

	UPROPERTY()
	AGolfBallCharacter* OwningPlayer;
	
	UFUNCTION()
	void Jump();

private:
};


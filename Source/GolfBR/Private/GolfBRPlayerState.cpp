// Fill out your copyright notice in the Description page of Project Settings.


#include "GolfBRPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

void AGolfBRPlayerState::PostInitializeComponents() {
	Super::PostInitializeComponents();
	
}

void AGolfBRPlayerState::CopyProperties(APlayerState* PlayerState) {
	Super::CopyProperties(PlayerState);
	SetIsSpectator(PlayerState->IsSpectator());
}

void AGolfBRPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGolfBRPlayerState, Team);
}

void AGolfBRPlayerState::SetPlayerNameExposed(FString PlayerString) {

	//bUseCustomPlayerNames = true;

	//PlayerString = "Player";
	//PlayerString = TEXT("Player %i", );
	//SetOldPlayerName(PlayerString);
	SetPlayerName(PlayerString);
	//SetPlayerNameInternal(PlayerString);
	//UE_LOG(LogTemp, Error, TEXT("yoyoyooyoyo: %s"), *PlayerString);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GolfBRGameState.h"
#include "Net/UnrealNetwork.h"

void AGolfBRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGolfBRGameState, LatestEvent);
	DOREPLIFETIME(AGolfBRGameState, WinningTeam);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GolfBRPlayerState.h"
#include "Net/UnrealNetwork.h"

void AGolfBRPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGolfBRPlayerState, Team);
}
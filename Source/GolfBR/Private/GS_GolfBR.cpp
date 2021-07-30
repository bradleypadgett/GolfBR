// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_GolfBR.h"

void AGS_GolfBR::GetPlayers(TArray<APlayerState*>& Players)
{
	for (auto PlayerState : PlayerArray)
		Players.Add(PlayerState);
}
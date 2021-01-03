// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GolfBRHud.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class GOLFBR_API AGolfBRHud : public AHUD
{
	GENERATED_BODY()
	
public:
	AGolfBRHud();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		TSubclassOf<UUserWidget> GameWidgetClass;
};

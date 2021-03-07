// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CustomMovementMode.generated.h"

#define EnumToString(EnumClassName, ValueOfEnum) UTextUtil::GetEnumValueAsString<EnumClassName>(FString(TEXT(#EnumClassName)), (ValueOfEnum))

/**
 * 
 */

UENUM(BlueprintType)
enum class EVictory : uint8 {
	VE_Dance       UMETA(DisplayName = "Dance"),
	VE_Rain        UMETA(DisplayName = "Rain"),
	VE_Song        UMETA(DisplayName = "Song"),
};
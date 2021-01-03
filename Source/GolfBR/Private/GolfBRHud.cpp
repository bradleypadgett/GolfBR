// Fill out your copyright notice in the Description page of Project Settings.


#include "GolfBRHud.h"
#include "Blueprint/UserWidget.h"

AGolfBRHud::AGolfBRHud() {
	static ConstructorHelpers::FClassFinder<UUserWidget> GameObj(TEXT("/Game/GolfBR/UI/UI_Game"));
	GameWidgetClass = GameObj.Class;
}

void AGolfBRHud::BeginPlay() {
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->bShowMouseCursor = false;
	}

	if (GameWidgetClass != nullptr) {
		UUserWidget* GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
		if (GameWidget != nullptr) {
			GameWidget->AddToViewport();
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "Players/GolfBallCharacter.h"
#include "Players/GolfBallPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"


AGolfBallController::AGolfBallController() {

}

void AGolfBallController::BeginPlay() {
	Super::BeginPlay();
	OwningPlayer = Cast<AGolfBallCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AGolfBallController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AGolfBallController::Jump);
}

void AGolfBallController::Jump() {
	OwningPlayer->PlayerJump(FVector(0.0f, 0.0f, 2500.0f));
}

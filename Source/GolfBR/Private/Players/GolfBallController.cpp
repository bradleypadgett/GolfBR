// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "Players/GolfBallPlayer.h"
#include "Kismet/GameplayStatics.h"


AGolfBallController::AGolfBallController() {

}

void AGolfBallController::BeginPlay() {	
	Super::BeginPlay();

	AGolfBallPlayer* GolfBallPlayer = Cast<AGolfBallPlayer>(GetPawn());

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("waa"));

	if (GolfBallPlayer->IsA(AGolfBallPlayer::StaticClass())) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("yay"));

	}
}

void AGolfBallController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AGolfBallController::Jump);

}

void AGolfBallController::Jump() {
	
	//FVector Impulse = FVector(0, 0, 100);
	//AddImpulse(Impulse, "", false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}



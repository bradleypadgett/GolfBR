// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "Players/GolfBallCharacter.h"
#include "Players/GolfBallPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpectatorPawn.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "Blueprint/WidgetLayoutLibrary.h"



AGolfBallController::AGolfBallController() {
	//helps with servertravel crash?
	bAlwaysRelevant = true;
}


void AGolfBallController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGolfBallController, OldPawn);
}

void AGolfBallController::BeginPlay() {
	Super::BeginPlay();
	OwningPlayer = Cast<AGolfBallCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AGolfBallController::PreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel) {
	Super::PreClientTravel(PendingURL, TravelType, bIsSeamlessTravel);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void AGolfBallController::ChangeState_To_Spectator()
{
	//APawn* Player = GetPawn();
	//if (OwningPlayer) {
		GetPawn()->SetActorHiddenInGame(true);
	//}

	ChangeState(NAME_Spectating);
	ClientGotoState(NAME_Spectating);

	//if (PlayerState) {
		PlayerState->SetIsSpectator(true);
		//PlayerState->SetIsOnlyASpectator(true);
	//}
}

void AGolfBallController::ChangeState_To_Player()
{
	ChangeState(NAME_Playing);
	ClientGotoState(NAME_Playing);

	if (PlayerState) {
		PlayerState->SetIsSpectator(false);
		//PlayerState->SetIsOnlyASpectator(false);

		if (OldPawn) {
			UnPossess();
			Possess(OldPawn);
			GetPawn()->SetActorHiddenInGame(false);
		}
	}
}
	
void AGolfBallController::PossessSpectator(ASpectatorPawn* SpawnedSpectator) {
	
	Spectator = SpawnedSpectator;

	UnPossess();
	Possess(Spectator);
}

void AGolfBallController::PossessPlayer() {

	UnPossess();

	if (Spectator) {
		Spectator->Destroy();
	}	

	if (OldPawn) {
		Possess(OldPawn);
	}
}

void AGolfBallController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	if (GetStateName() == NAME_Spectating)
	{
		AutoManageActiveCameraTarget(GetSpectatorPawn());
	}
}

void AGolfBallController::StartSpectating()
{
	if (!HasAuthority())
		return;

	ChangeState(NAME_Spectating);
	Client_StartSpectating();
}

void AGolfBallController::StartPlaying()
{
	if (!HasAuthority())
		return;

	ChangeState(NAME_Playing);
	ClientGotoState(NAME_Playing);
}

void AGolfBallController::Client_StartSpectating_Implementation()
{
	if (PlayerCameraManager)
		SetSpawnLocation(PlayerCameraManager->GetCameraLocation());

	ChangeState(NAME_Spectating);
}



void AGolfBallController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AGolfBallController::Jump);
}

void AGolfBallController::Jump() {
	OwningPlayer->PlayerJump(FVector(0.0f, 0.0f, 2500.0f));
}

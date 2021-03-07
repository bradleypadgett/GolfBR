// Fill out your copyright notice in the Description page of Project Settings.


#include "GolfBRWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GolfBRPlayerState.h"
#include "GolfBRGameState.h"
#include "GolfBRGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGolfBRWidget::NativeConstruct() {
	Super::NativeConstruct();

	TeamNameTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TeamName"));
	TeammateCountTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TeammateCount"));
	EventTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Event"));
	PingTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Ping"));

	//GetWorld()->GetTimerManager().SetTimer(SetTeammateCountHandle, this, &UGolfBRWidget::SetTeammateCount, 1.0f, true, 1.0f);
	//GetWorld()->GetTimerManager().SetTimer(SetLatestEventHandle, this, &UGolfBRWidget::SetLatestEvent, 1.0f, true, 1.0f);
	//GetWorld()->GetTimerManager().SetTimer(SetAveragePlayerLatencyHandle, this, &UGolfBRWidget::SetAveragePlayerLatency, 1.0f, true, 1.0f);
}

void UGolfBRWidget::NativeDestruct() {
	GetWorld()->GetTimerManager().ClearTimer(SetTeammateCountHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetLatestEventHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetAveragePlayerLatencyHandle);
	Super::NativeDestruct();
}

void UGolfBRWidget::SetTeammateCount() {
	FString OwningPlayerTeam;
	APlayerState* OwningPlayerState = GetOwningPlayerState();

	if (OwningPlayerState != nullptr) {
		AGolfBRPlayerState* OwningGolfBRPlayerState = Cast<AGolfBRPlayerState>(OwningPlayerState);
		if (OwningGolfBRPlayerState != nullptr) {
			OwningPlayerTeam = OwningGolfBRPlayerState->Team;
			TeamNameTextBlock->SetText(FText::FromString("Team Name: " + OwningPlayerTeam));
		}
	}

	if (OwningPlayerTeam.Len() > 0) {
		TArray<APlayerState*> PlayerStates = GetWorld()->GetGameState()->PlayerArray;

			int TeammateCount = 0;

		for (APlayerState* PlayerState : PlayerStates) {
			if (PlayerState != nullptr) {
				AGolfBRPlayerState* GolfBRPlayerState = Cast<AGolfBRPlayerState>(PlayerState);
				if (GolfBRPlayerState != nullptr && GolfBRPlayerState->Team.Equals(OwningPlayerTeam)) {
					TeammateCount++;
				}
			}
		}

		TeammateCountTextBlock->SetText(FText::FromString("Teammates: " + FString::FromInt(TeammateCount)));
	}
}

void UGolfBRWidget::SetLatestEvent() {
	FString LatestEvent;
	FString WinningTeam;
	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (GameState != nullptr) {
		AGolfBRGameState* GolfBRGameState = Cast<AGolfBRGameState>(GameState);
		if (GolfBRGameState != nullptr) {
			LatestEvent = GolfBRGameState->LatestEvent;
			WinningTeam = GolfBRGameState->WinningTeam;
		}
	}

	if (LatestEvent.Len() > 0) {
		if (LatestEvent.Equals("GameEnded")) {
			FString OwningPlayerTeam;
			APlayerState* OwningPlayerState = GetOwningPlayerState();

			if (OwningPlayerState != nullptr) {
				AGolfBRPlayerState* OwningGolfBRPlayerState = Cast<AGolfBRPlayerState>(OwningPlayerState);
				if (OwningGolfBRPlayerState != nullptr) {
					OwningPlayerTeam = OwningGolfBRPlayerState->Team;
				}
			}
			
			if (WinningTeam.Len() > 0 && OwningPlayerTeam.Len() > 0) {
				FString GameOverMessage = "You and the " + OwningPlayerTeam;
				if (OwningPlayerTeam.Equals(WinningTeam)) {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " won!"));
				}
				else {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " lost :("));
				}
			}
		}
		else {
			EventTextBlock->SetText(FText::FromString(LatestEvent));
		}
	}
}

void UGolfBRWidget::SetAveragePlayerLatency() {
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UGolfBRGameInstance* GolfBRGameInstance = Cast<UGolfBRGameInstance>(GameInstance);
		if (GolfBRGameInstance != nullptr) {
			float TotalPlayerLatency = 0.0f;
			for (float PlayerLatency : GolfBRGameInstance->PlayerLatencies) {
				TotalPlayerLatency += PlayerLatency;
			}

			float AveragePlayerLatency = 60.0f;
			if (TotalPlayerLatency > 0) {
				AveragePlayerLatency = TotalPlayerLatency / GolfBRGameInstance->PlayerLatencies.Num();

				FString PingString = "Ping: " + FString::FromInt(FMath::RoundToInt(AveragePlayerLatency)) + "ms";
				PingTextBlock->SetText(FText::FromString(PingString));
			}
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "MainMenuWidget.generated.h"

class UWebBrowser;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class GOLFBR_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
		FTimerHandle SetAveragePlayerLatencyHandle;

	UPROPERTY()
		FTimerHandle PollMatchmakingHandle;
		

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	FHttpModule* HttpModule;

	UPROPERTY()
		FString LoginUrl;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		FString CallbackUrl;

	UPROPERTY()
		UWebBrowser* WebBrowser;

	UPROPERTY()
		UButton* MatchmakingButton;

	UPROPERTY()
		UTextBlock* WinsTextBlock;

	UPROPERTY()
		UTextBlock* LossesTextBlock;

	UPROPERTY()
		UTextBlock* PingTextBlock;

	UPROPERTY()
		UTextBlock* MatchmakingEventTextBlock;

	UPROPERTY()
		float AveragePlayerLatency;

	UPROPERTY()
		bool bSearchingForGame;

	UPROPERTY()
		FString RegionCode;

	UFUNCTION()
		void HandleLoginUrlChange();

	UFUNCTION()
		void SetAveragePlayerLatency();

	UFUNCTION()
		void OnMatchmakingButtonClicked();

	UFUNCTION()
		void PollMatchmaking();
	
	void OnExchangeCodeForTokensResponseReceieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetPlayerDataResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnStartMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnStopMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnPollMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};

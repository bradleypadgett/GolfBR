// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerSDK.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "GolfBRGameMode.generated.h"

USTRUCT()
struct FStartGameSessionState2
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	UPROPERTY()
		FString MatchmakingConfigurationArn;

	TMap<FString, Aws::GameLift::Server::Model::Player> PlayerIdToPlayer;
	
	FStartGameSessionState2() {
		Status = false;
	}
};

USTRUCT()
struct FUpdateGameSessionState2
{

	GENERATED_BODY();

	FUpdateGameSessionState2() {

	}
};

USTRUCT()
struct FProcessTerminateState2
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	long TerminationTime;

	FProcessTerminateState2() {
		Status = false;
		TerminationTime = 0L;
	}
};

USTRUCT()
struct FHealthCheckState2
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	FHealthCheckState2() {
		Status = false;
	}
};

UCLASS(minimalapi)
class AGolfBRGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGolfBRGameMode();
	
	void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	void Logout(AController* Exiting) override;

public:
	UPROPERTY()
		FTimerHandle CountDownUntilGameOverHandle;

	UPROPERTY()
		FTimerHandle EndGameHandle;

	UPROPERTY()
		FTimerHandle PickAWinningTeamHandle;

	UPROPERTY()
		FTimerHandle HandleProcessTerminationHandle;

	UPROPERTY()
		FTimerHandle HandleGameSessionUpdateHandle;

protected:
	void BeginPlay() override;

	FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

private:
	FHttpModule* HttpModule;

	UPROPERTY()
		FStartGameSessionState2 StartGameSessionState;

	UPROPERTY()
		FUpdateGameSessionState2 UpdateGameSessionState;

	UPROPERTY()
		FProcessTerminateState2 ProcessTerminateState;
	
	UPROPERTY()
		FHealthCheckState2 HealthCheckState;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		FString ServerPassword;

	UPROPERTY()
		int RemainingGameTime;

	UPROPERTY()
		bool GameSessionActivated;

	UFUNCTION()
		void CountDownUntilGameOver();

	UFUNCTION()
		void EndGame();

	UFUNCTION()
		void PickAWinningTeam();

	UFUNCTION()
		void HandleProcessTermination();

	UFUNCTION()
		void HandleGameSessionUpdate();

	void OnRecordMatchResultResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};




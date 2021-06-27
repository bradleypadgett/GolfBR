// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallReplicationComponent.h"

// Sets default values for this component's properties
UGolfBallReplicationComponent::UGolfBallReplicationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGolfBallReplicationComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("i did it yay"));
	
}


// Called every frame
void UGolfBallReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


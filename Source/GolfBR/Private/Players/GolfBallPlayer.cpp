// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/GolfBallPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/GameViewportClient.h"
#include "Components/ArrowComponent.h"
#include "Players/GolfBallCameraComponent.h"
#include "Players/GolfBallMovementComponent.h"
#include "Players/GolfBallReplicationComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector2D.h"

// Sets default values
AGolfBallPlayer::AGolfBallPlayer()
{ 
	//helps with servertravel crash?
	bAlwaysRelevant = true;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	GolfBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GolfBall"));

	RootComponent = GolfBall;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GolfBall);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ArrowCenter = CreateDefaultSubobject<USceneComponent>(TEXT("Arrow Center"));
	ArrowCenter->SetupAttachment(GolfBall);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(ArrowCenter);

	CameraComponent = CreateDefaultSubobject<UGolfBallCameraComponent>(TEXT("Camera Component"));
	MovementComponent = CreateDefaultSubobject<UGolfBallMovementComponent>(TEXT("Movement Component"));
	ReplicationComponent = CreateDefaultSubobject<UGolfBallReplicationComponent>(TEXT("Replication Component"));


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

// Called when the game starts or when spawned
void AGolfBallPlayer::BeginPlay()
{
	Super::BeginPlay();
	FVector2D VectorTest = (1.f,1.f);
	VectorTest.DotProduct(VectorTest, VectorTest);
	VectorTest.operator*((1.f,1.f));
}


// Called every frame
void AGolfBallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FString role;
	//UEnum::GetValueAsString(GetLocalRole(), role);
	//DrawDebugString(GetWorld(), FVector(0, 0, 10), role, this, FColor::White, DeltaTime);

	// below works - just not applicable rn
	//bool bGamepadAttached = FSlateApplication::Get().IsGamepadAttached();

}


// Called to bind functionality to input
void AGolfBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	
	
	PlayerInputComponent->BindAxis("Turn", CameraComponent, &UGolfBallCameraComponent::Turn);
	PlayerInputComponent->BindAxis("TurnRate", CameraComponent, &UGolfBallCameraComponent::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", CameraComponent, &UGolfBallCameraComponent::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", CameraComponent, &UGolfBallCameraComponent::LookUpAtRate);

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UGolfBallMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UGolfBallMovementComponent::MoveRight);

	PlayerInputComponent->BindAction("Charge", IE_Pressed, MovementComponent, &UGolfBallMovementComponent::ChargeShotSetup);
	PlayerInputComponent->BindAction("Charge", IE_Released, MovementComponent, &UGolfBallMovementComponent::ShootBall);
	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, MovementComponent, &UGolfBallMovementComponent::Jump);
	
}


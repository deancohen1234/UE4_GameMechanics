// Fill out your copyright notice in the Description page of Project Settings.

#include "SmashCameraFollowComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USmashCameraFollowComponent::USmashCameraFollowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USmashCameraFollowComponent::BeginPlay()
{
	Super::BeginPlay();


	OwningPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (OwningPlayerController)
	{
		int32 ScreenWidth = 0;
		int32 ScreenHeight = 0;
		OwningPlayerController->GetViewportSize(ScreenWidth, ScreenHeight);

		PreferredPlayerScreenWidth = ScreenWidth - PreferredPlayerScreenPadding;
	}
	
}


// Called every frame
void USmashCameraFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PanCamera(Player1, Player2);

	float ZoomAmount = CalculateZoom(Player1, Player2);

	ZoomCamera(ZoomAmount, DeltaTime);
}

void USmashCameraFollowComponent::PanCamera(AActor* player1, AActor* player2) 
{
	if (GetOwner() == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Owner of Camera Follow is null!!"));
	}

	if (player1 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player 1 Actor is null!!"));
		return;
	}

	if (player2 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player 1 Actor is null!!"));
		return;
	}

	FVector player1Loc = player1->GetActorLocation();
	FVector player2Loc = player2->GetActorLocation();

	FVector playersLocMidpoint = (player1Loc + player2Loc) / 2.0f; //get midpoint between both players

	FVector newCameraPosition = FVector(GetOwner()->GetActorLocation().X, playersLocMidpoint.Y, GetOwner()->GetActorLocation().Z);
	GetOwner()->SetActorLocation(newCameraPosition);
}

float USmashCameraFollowComponent::CalculateZoom(AActor * player1, AActor * player2)
{
	if (OwningPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner of Camera Follow is null!!"));
		return 0;
	}

	if (player1 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player 1 Actor is null!!"));
		return 0;
	}

	if (player2 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player 1 Actor is null!!"));
		return 0;
	}

	FVector2D PlayerTwoScreenLoc;
	//FVector2D PlayerTwoScreenLoc;
	OwningPlayerController->ProjectWorldLocationToScreen(player1->GetActorLocation(), PlayerTwoScreenLoc); //get screen loc for player 1
	//GetOwner()->GetController()->ProjectWorldLocationToScreen(player2->GetActorLocation(), PlayerTwoScreenLoc); //get screen loc for player 2

	//if Player Screen Loc < PreferredPlayerScreenWidth => ZoomOut
	//if Player Screen Loc > PreferredPlayerScreenWidth => ZoomIn
	float PlayerOffDistance = PreferredPlayerScreenWidth - PlayerTwoScreenLoc.X; //how far away is player from correct zoom location;

	//UE_LOG(LogTemp, Error, TEXT("Player Off Dist: %f"), PlayerOffDistance);

	return PlayerOffDistance * -1;
}

//zoom direction is X by lerping
void USmashCameraFollowComponent::ZoomCamera(float zoomAmount, float deltaTime)
{
	FVector desiredCameraPosition = FVector(GetOwner()->GetActorLocation().X + zoomAmount, GetOwner()->GetActorLocation().Y, GetOwner()->GetActorLocation().Z);

	FVector newCameraPosition = FMath::Lerp(GetOwner()->GetActorLocation(), desiredCameraPosition, deltaTime * ZoomSpeed);
	GetOwner()->SetActorLocation(newCameraPosition);
}


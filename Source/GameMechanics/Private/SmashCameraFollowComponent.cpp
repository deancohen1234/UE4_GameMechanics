// Fill out your copyright notice in the Description page of Project Settings.

#include "SmashCameraFollowComponent.h"


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

	// ...
	
}


// Called every frame
void USmashCameraFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PanCamera(Player1, Player2);

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


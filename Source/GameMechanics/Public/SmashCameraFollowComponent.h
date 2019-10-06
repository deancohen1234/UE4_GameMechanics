// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SmashCameraFollowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEMECHANICS_API USmashCameraFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USmashCameraFollowComponent();

protected:

	UPROPERTY(EditAnywhere)
	AActor* Player1 = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* Player2 = nullptr;

	UPROPERTY(EditAnywhere)
	int PreferredPlayerScreenPadding = 1000; //in pixels

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 10.0f; //in pixels

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void PanCamera(AActor* player1, AActor* player2); //pan camera horizontally and vertically to view both players
	float CalculateZoom(AActor* player1, AActor* player2); //zoom camera to fit both players

	void ZoomCamera(float zoomAmount, float deltaTime);

	APlayerController* OwningPlayerController;
	int32 PreferredPlayerScreenWidth; //set on Begin
	
};

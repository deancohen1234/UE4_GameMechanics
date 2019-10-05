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

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void PanCamera(AActor* player1, AActor* player2); //pan camera horizontally and vertically to view both players
	
};

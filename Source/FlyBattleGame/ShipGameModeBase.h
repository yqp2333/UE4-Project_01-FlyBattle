// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShipGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLYBATTLEGAME_API AShipGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AShipGameModeBase();
	
protected:

	UPROPERTY(BlueprintReadOnly)
	int Score;

public:
	void IncreaseScore();

};

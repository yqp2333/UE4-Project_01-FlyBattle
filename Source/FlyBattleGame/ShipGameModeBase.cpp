// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipGameModeBase.h"

AShipGameModeBase::AShipGameModeBase()
{
	Score = 0;
}

void AShipGameModeBase::IncreaseScore()
{
	Score++;
}

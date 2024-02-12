// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameSaveSystem.generated.h"

// Maybe create item struct for inventory

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
	GENERATED_BODY()

public:

	/* Identifier for which Actor this belongs to */
	UPROPERTY() FName ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY() FTransform Transform;

	//UPROPERTY() float Sanity;

	// Inventory item store here somewhere - array of items:

};

USTRUCT(BlueprintType)
struct FInteractiveItemsData
{
	GENERATED_BODY()

public:

	/* Identifier for which Actor this belongs to */
	UPROPERTY() TArray<ABaseInspection*>ItemArray;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY() TArray<FTransform>Transform;

	//UPROPERTY() float Sanity;

	// Inventory item store here somewhere - array of items:

};

/**
 * 
 */
UCLASS()
class TIMETEST_API UGameSaveSystem : public USaveGame
{
	GENERATED_BODY()
	
public:

	UGameSaveSystem();

	UPROPERTY() FPlayerSaveData P_Save;
	UPROPERTY() FInteractiveItemsData Item_save;
};

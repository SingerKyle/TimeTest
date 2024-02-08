// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameSaveSystem.h"
#include "SaveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TIMETEST_API USaveGameInstance : public UGameInstance
{
    GENERATED_BODY()

	USaveGameInstance();

    virtual void Init() override;
public:
    //Function to Create a file for saving
    void CreateSaveFile();

    // Function to save the game
    UFUNCTION(BlueprintCallable, Category = "SaveGame") void SaveGame();

    // Function to load the game
    UFUNCTION(BlueprintCallable, Category = "SaveGame") void LoadGame();

    // Save file name
    const FString SaveSlotName = TEXT("Save_01");
    const uint32 SaveUserIndex = 0;

    // Functions to save player and item locations / activity etc
    void SavePlayerCharacter(UGameSaveSystem* SaveSlot);
    void SaveInteractableItems();
};

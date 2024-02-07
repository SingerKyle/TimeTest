// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameInstance.h"

#include "TimeTestCharacter.h"
#include "Kismet/GameplayStatics.h"


USaveGameInstance::USaveGameInstance()
{
	
}

void USaveGameInstance::Init()
{
	Super::Init();
	if(!UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{ 
		CreateSaveFile();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Create new save file!"));
	}
}

void USaveGameInstance::CreateSaveFile()
{
    // Create a new save object
	UGameSaveSystem* SaveSlot = Cast<UGameSaveSystem>(UGameplayStatics::CreateSaveGameObject(UGameSaveSystem::StaticClass()));
	UGameplayStatics::SaveGameToSlot(SaveSlot, SaveSlotName, 0);

}

void USaveGameInstance::SaveGame()
{
	// initialise save game object
	UGameSaveSystem* SaveSlot = Cast<UGameSaveSystem>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	// if valid use for saving
	if (SaveSlot != nullptr)
	{
		SavePlayerCharacter(SaveSlot);
		UGameplayStatics::SaveGameToSlot(SaveSlot, SaveSlotName, 0);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving!"));
	}
	else
	{
		CreateSaveFile();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Create new save file in savegame func!"));
	}
}

void USaveGameInstance::LoadGame()
{
   // retrieve load data
	UGameSaveSystem* SaveSlot = Cast<UGameSaveSystem>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	// if valid data
	if (SaveSlot != nullptr)
	{
		ATimeTestCharacter* player = Cast<ATimeTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		player->SetActorTransform(SaveSlot->P_Save.Transform);
		player->GetController()->SetControlRotation(SaveSlot->P_Save.Transform.GetRotation().Rotator());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Loading!"));
	}
	else
	{
		
	}
}

void USaveGameInstance::SavePlayerCharacter(UGameSaveSystem* SaveSlot)
{
	// initialise save game object
	ATimeTestCharacter* player = Cast<ATimeTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player && SaveSlot)
	{
		// get info from player
		SaveSlot->P_Save.Transform = player->GetTransform();
		SaveSlot->P_Save.Transform.SetRotation(player->GetControlRotation().Quaternion());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving player!"));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameInstance.h"

#include "BaseInspection.h"
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
		SaveInteractableItems(SaveSlot);
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

		// Load Items

		TArray<AActor*> InteractiveItems;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseInspection::StaticClass(), InteractiveItems);

		bool founditem = false;

		for (int x = 0; x < InteractiveItems.Num(); x++)
		{
			for( int y = 0; y < SaveSlot->Item_save.ItemArray.Num(); y++)
			{
				if (InteractiveItems[x]->GetActorLocation() == SaveSlot->Item_save.ItemArray[y]->GetActorLocation())
				{
					founditem = true;
					break;
				}
			}

			if (!founditem)
			{
				GetWorld()->DestroyActor(InteractiveItems[x]);
			}
			else
			{
				founditem = false;
			}
		}
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

void USaveGameInstance::SaveInteractableItems(UGameSaveSystem* SaveSlot)
{
	TArray<AActor*> InteractiveItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseInspection::StaticClass(), InteractiveItems);

	UE_LOG(LogTemp, Warning, TEXT("The number of elements in the array is: %d"), InteractiveItems.Num());

	SaveSlot->Item_save.ItemArray.Empty();

	for (int i = 0; i < InteractiveItems.Num(); i++)
	{
		ABaseInspection* InteractiveItem = Cast<ABaseInspection>(InteractiveItems[i]);
		if (InteractiveItem && SaveSlot)
		{
			SaveSlot->Item_save.ItemArray.Add(InteractiveItem);
			SaveSlot->Item_save.Transform.Add(InteractiveItem->GetActorTransform());
		}
	}
}

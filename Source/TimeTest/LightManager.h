// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Light.h"
#include "LightManager.generated.h"

UENUM(BlueprintType)
enum class MyRooms : uint8
{
	COLONNADE UMETA(DisplayName = "Colonnade"),
	DININGROOM UMETA(DisplayName = "Dining Room"),
	CORRIDOR UMETA(DisplayName = "Corridor"),
	KITCHEN UMETA(DisplayName = "Kitchen"),
	LIBRARY UMETA(DisplayName = "Library"),
	CLASSROOM UMETA(DisplayName = "ClassRoom"),
	DORM_BOYS UMETA(DisplayName = "Boys Dorm"),
	DORM_GIRLS UMETA(DisplayName = "Girls Dorm"),
	MATRONROOM UMETA(DisplayName = "Matron Room"),
	ATTIC UMETA(DisplayName = "Attic"),
	CHAPEL UMETA(DisplayName = "Chapel"),
	BATHROOMS UMETA(DisplayName = "Bathrooms"),
};

USTRUCT(BlueprintType)
struct FLightingTestStruct
{
	GENERATED_BODY()

	MyRooms room = MyRooms::ATTIC;
};

/**
 * TODO:
 * ENUM/Struct of rooms in house for each light to be placed in
 *
 * Colour Control function (HSL)
 * Enable disable room lighting function
 * Brightness function
 * Cone settings
 * Attenuation
 *
 * Function to add light to specific room
 * Function to get and set rooms
 *
 */

UCLASS()
class TIMETEST_API ALightManager : public ALight
{
	GENERATED_BODY()
	
};

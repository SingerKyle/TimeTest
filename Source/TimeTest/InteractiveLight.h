// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInspection.h"
#include "Components/PointLightComponent.h"
#include "InteractiveLight.generated.h"

UCLASS()
class TIMETEST_API AInteractiveLight : public ABaseInspection
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void Interact_Implementation() override;

	UPROPERTY() bool state;

	UPROPERTY(EditAnywhere) int intensity;

	UPROPERTY(EditAnywhere) UPointLightComponent* Light;
};

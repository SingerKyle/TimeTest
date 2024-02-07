// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "InspectItem.generated.h"

UCLASS()
class TIMETEST_API AInspectItem : public ABaseInspection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) USphereComponent* ItemTrigger;
	
public:	
	// Sets default values for this actor's properties
	AInspectItem();

	//UPROPERTY(EditAnywhere) UStaticMeshComponent* ItemMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

};

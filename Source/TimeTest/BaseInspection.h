// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "TimeTest.h"
#include "BaseInspection.generated.h"

UCLASS()
class TIMETEST_API ABaseInspection : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInspection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool interactive = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	bool getInteractive() { return interactive; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly) USceneComponent* _rootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMeshComponent* ItemMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly) FInventoryItem ItemData;

	//Audio
	//UPROPERTY(EditAnywhere, Category = "Audio") class USoundBase* throwSound;
};

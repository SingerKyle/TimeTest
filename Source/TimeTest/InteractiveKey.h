// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "InteractiveKey.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeyPickup);
UCLASS()
class TIMETEST_API AInteractiveKey : public ABaseInspection
{
	GENERATED_BODY()
	
	

public:	
	// Sets default values for this actor's properties
	AInteractiveKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable) FOnKeyPickup KeyPickup;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
};

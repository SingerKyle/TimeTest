// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GhostChild.generated.h"

UCLASS()
class TIMETEST_API AGhostChild : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGhostChild();

	UBehaviorTree* getBehaviorTree() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// behaviour tree
	UPROPERTY(EditAnywhere, Category = "Enemy AI") UBehaviorTree* tree;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

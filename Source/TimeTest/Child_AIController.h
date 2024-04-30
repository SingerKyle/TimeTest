// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AGhostChild;

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Child_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TIMETEST_API AChild_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit AChild_AIController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* inPawn) override;

private:
	class UAISenseConfig_Sight* sightSetup;

	void initPerception();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetPerceptionInfoUpdated, AActor*, Actor, FAIStimulus, Stimulus);

	UPROPERTY()
	FOnTargetPerceptionInfoUpdated OnTargetPerceptionInfoUpdated;

	UFUNCTION() void onTargetInSight(AActor* actor, FAIStimulus const Stimulus);
};

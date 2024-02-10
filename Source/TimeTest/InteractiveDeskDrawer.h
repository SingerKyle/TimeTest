// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractiveDeskDrawer.generated.h"

UCLASS()
class TIMETEST_API AInteractiveDeskDrawer : public ABaseInspection
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveDeskDrawer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool closed;

	virtual void Interact_Implementation() override;

	UFUNCTION() void Test(float val);

	// setup timeline
	FOnTimelineFloat TimelineEvent{};
	FOnTimelineEvent TimelineProgress{};

	UPROPERTY(EditAnywhere) UTimelineComponent* DrawerTimeline;

	UPROPERTY(EditAnywhere) UCurveFloat* CurveFloat;

};

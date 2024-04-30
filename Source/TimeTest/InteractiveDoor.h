// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "InteractiveDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpened);

UCLASS()
class TIMETEST_API AInteractiveDoor : public ABaseInspection
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractiveDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable) FOnDoorOpened OnDoorOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UStaticMeshComponent* DoorHandle;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool closed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool locked;

	virtual void Interact_Implementation() override;

	UFUNCTION() void OnFinish();
	UFUNCTION() void Test(float val);

	// setup timeline
	FOnTimelineFloat TimelineEvent{};
	FOnTimelineEvent TimelineProgress{};

	UPROPERTY(EditAnywhere) UTimelineComponent* DoorTimeline;

	UPROPERTY(EditAnywhere) UCurveFloat* CurveFloat;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SanityMeter.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMETEST_API USanityMeter : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USanityMeter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() void TickSanity(float DeltaTime);
	UFUNCTION() void handleParanoiaActivities();

	UFUNCTION(BlueprintCallable)
	void updateEvent(float paranoia);
	
	UFUNCTION(BlueprintCallable)
	float getParanoia();
	
	uint8_t curEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float curParanoia;
	
	float ParanoidIncrease;
	float MaxParanoidIncrease;
	float Time = 0;
	float Counter = 0;
};

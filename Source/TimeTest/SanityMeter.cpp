// Fill out your copyright notice in the Description page of Project Settings.


#include "SanityMeter.h"

// Sets default values for this component's properties
USanityMeter::USanityMeter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	curParanoia = 0;
	ParanoidIncrease = 0.8f;
	MaxParanoidIncrease = 2.6f;
}


// Called when the game starts
void USanityMeter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USanityMeter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickSanity(DeltaTime);
}


void USanityMeter::TickSanity(float DeltaTime)
{
	if (Time >= 10.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Paranoria: %.2f"), curParanoia));
		Time = 0.0f;
		curParanoia += ParanoidIncrease;
		
		(void)handleParanoiaActivities();
	}
	
	if (Counter >= 60.1f)
	{
		ParanoidIncrease += 0.2;
		Counter = 0;
	}
	
	Counter += DeltaTime;
	Time += DeltaTime;
}

void USanityMeter::handleParanoiaActivities() {
	/*
	* 0 - 20% → Normal breathing, paranormal activities
	* 21 - 50% → Slightly heavier and quicker breathing, Eerie sounds during exploration
	* 51 - 80% → Camera screen flickering, few VFX from the second realm, character starts walking 5% quicker
	* 81 - 94% →  Former stages + heavy breathing, switching to the other realm for a second (random)
	* 95 - 100% → Losing control over the character, endgame state, ending animation triggers
	*/

	uint8_t prevEvent = curEvent;
	
	if(curParanoia >= 21 && curParanoia <= 50 && curEvent == 0) {
		//TODO; 21 - 50% → Slightly heavier and quicker breathing, Eerie sounds during exploration
		curEvent++;
	} else if(curParanoia >= 51 && curParanoia <= 80 && curEvent == 1) {
		//TODO; 51 - 80% → Camera screen flickering, few VFX from the second realm, character starts walking 5% quicker
		curEvent++;
	} else if(curParanoia >= 81 && curParanoia <= 94 && curEvent == 2) {
		//TODO; 81 - 94% →  Former stages + heavy breathing, switching to the other realm for a second (random)
		curEvent++;
	} else if(curParanoia >= 95 && curParanoia <= 100 && curEvent == 3) {
		//TODO; 95 - 100% → Losing control over the character, endgame state, ending animation triggers
		curEvent++;
	}
	
	if(prevEvent != curEvent) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Updated event; %d"), curEvent));
		updateEvent(curParanoia);
	}
}

void USanityMeter::updateEvent(float paranoia) {
	
}

float USanityMeter::getParanoia() {
	return curParanoia;
}

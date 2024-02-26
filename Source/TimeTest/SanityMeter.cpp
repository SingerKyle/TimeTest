// Fill out your copyright notice in the Description page of Project Settings.


#include "SanityMeter.h"

// Sets default values for this component's properties
USanityMeter::USanityMeter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ThisMuchParanoid = 0;
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
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Paranoria: %.2f"), ThisMuchParanoid));

	if (Time >= 10.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Paranoria: %.2f"), ThisMuchParanoid));
		Time = 0.0f;
		ThisMuchParanoid += ParanoidIncrease;
	}

	if (Counter >= 60.1f)
	{
		ParanoidIncrease += 0.2;
		Counter = 0;
	}

	Counter += DeltaTime;
	Time += DeltaTime;
}


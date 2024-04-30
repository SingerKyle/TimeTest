// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveKey.h"

// Sets default values
AInteractiveKey::AInteractiveKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveKey::Interact_Implementation()
{
	KeyPickup.Broadcast();
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDoor.h"

// Sets default values
AInteractiveDoor::AInteractiveDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// setup timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	TimelineEvent.BindUFunction(this, FName("Test"));
	TimelineProgress.BindUFunction(this, FName("OnFinish"));
}

// Called when the game starts or when spawned
void AInteractiveDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveDoor::Interact_Implementation()
{

}


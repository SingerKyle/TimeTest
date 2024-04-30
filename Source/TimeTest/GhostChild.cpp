// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostChild.h"

// Sets default values
AGhostChild::AGhostChild()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//const TCHAR* name(TEXT("Ghost Mesh"));
	//GetMesh()->Rename(name);
}

UBehaviorTree* AGhostChild::getBehaviorTree() const
{
	return tree;
}

// Called when the game starts or when spawned
void AGhostChild::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostChild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGhostChild::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLight.h"
#include "Components/PointLightComponent.h"

// Sets default values
AInteractiveLight::AInteractiveLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/StarterContent/Props/SM_Lamp_Wall.SM_Lamp_Wall'"));
	if (ItemMeshComp.Succeeded())
	{
		UStaticMesh* ObjectMesh = ItemMeshComp.Object;
		ItemMesh->SetStaticMesh(ObjectMesh);
		ItemMesh->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AInteractiveLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


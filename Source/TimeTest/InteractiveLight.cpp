// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLight.h"
#include "Components/PointLightComponent.h"

// Sets default values
AInteractiveLight::AInteractiveLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	state = true;
	intensity = 2000;

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);
	Light->SetIntensity(intensity);
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/Assets/Mesh_Table_Lamp.Mesh_Table_Lamp'"));

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

void AInteractiveLight::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (state)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(intensity);
	}

	state = !state;
}

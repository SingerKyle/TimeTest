// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectItem.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AInspectItem::AInspectItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

/*	ItemTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Item Trigger"));
	//RootComponent = ItemTrigger;
	if (ItemTrigger)
	{
		ItemTrigger->SetSphereRadius(150.f);
		ItemTrigger->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // Set collision profile
		ItemTrigger->SetupAttachment(RootComponent);
	}*/

	interactive = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (ItemMeshComp.Succeeded())
	{
		UStaticMesh* ObjectMesh = ItemMeshComp.Object;
		//ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
		ItemMesh->SetStaticMesh(ObjectMesh);
		ItemMesh->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AInspectItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInspectItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInspectItem::Interact_Implementation()
{
	ABaseInspection::Interact_Implementation();

	// Save item to inventory - destroy for now
	
	//Destroy();

	
}


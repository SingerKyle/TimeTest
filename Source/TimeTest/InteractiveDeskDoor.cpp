// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDeskDoor.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveDeskDoor::AInteractiveDeskDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/3-Assets/Mesh_Desk_Door_01_01.Mesh_Desk_Door_01_01'"));
	if (ItemMeshComp.Succeeded())
	{
		UStaticMesh* ObjectMesh = ItemMeshComp.Object;
		ItemMesh->SetStaticMesh(ObjectMesh);
		ItemMesh->SetupAttachment(RootComponent);
	}

	// setup timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	TimelineEvent.BindUFunction(this, FName("Test"));
	TimelineProgress.BindUFunction(this, FName("OnFinish"));

	closed = true;
}

// Called when the game starts or when spawned
void AInteractiveDeskDoor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		DoorTimeline->AddInterpFloat(CurveFloat, TimelineEvent, FName("Alpha"));
		DoorTimeline->SetTimelineFinishedFunc(TimelineProgress);
		DoorTimeline->SetLooping(false);
	}
}

// Called every frame
void AInteractiveDeskDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveDeskDoor::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (closed)
	{
		DoorTimeline->PlayFromStart();
	}
	else
	{
		DoorTimeline->ReverseFromEnd();
	}

	closed = !closed;
}

void AInteractiveDeskDoor::Test(float val)
{
	ItemMesh->SetRelativeRotation(FRotator(0, UKismetMathLibrary::Ease(0, 110, val, EEasingFunc::SinusoidalInOut), 0));
}


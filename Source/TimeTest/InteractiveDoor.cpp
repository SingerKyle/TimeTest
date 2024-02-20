// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveDoor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveDoor::AInteractiveDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/AbandonedPlaySchool/Meshes/SM_Door.SM_Door'"));

	if (ItemMeshComp.Succeeded())
	{
		UStaticMesh* ObjectMesh = ItemMeshComp.Object;
		//ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
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
void AInteractiveDoor::BeginPlay()
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
void AInteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveDoor::Interact_Implementation()
{
	if (closed)
	{
		DoorTimeline->PlayFromStart();
	}
	else
	{
		DoorTimeline->ReverseFromEnd();
	}

	closed = !closed;
	ABaseInspection::Interact_Implementation();

}

void AInteractiveDoor::OnFinish()
{
	
}

void AInteractiveDoor::Test(float val)
{
	ItemMesh->SetRelativeRotation(FRotator(0, UKismetMathLibrary::Ease(0, 110, val, EEasingFunc::SinusoidalInOut), 0));
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDeskDrawer.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractiveDeskDrawer::AInteractiveDeskDrawer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMeshComp(TEXT("'/Game/3-Assets/Mesh_Desk_Drawer_01_01.Mesh_Desk_Drawer_01_01'"));
	if (ItemMeshComp.Succeeded())
	{
		UStaticMesh* ObjectMesh = ItemMeshComp.Object;
		//ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
		ItemMesh->SetStaticMesh(ObjectMesh);
		ItemMesh->SetupAttachment(RootComponent);
	}

	// setup timeline
	DrawerTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	TimelineEvent.BindUFunction(this, FName("Test"));
	TimelineProgress.BindUFunction(this, FName("OnFinish"));

	closed = true;

}

// Called when the game starts or when spawned
void AInteractiveDeskDrawer::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		DrawerTimeline->AddInterpFloat(CurveFloat, TimelineEvent, FName("Alpha"));
		DrawerTimeline->SetTimelineFinishedFunc(TimelineProgress);
		DrawerTimeline->SetLooping(false);
	}
}

// Called every frame
void AInteractiveDeskDrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveDeskDrawer::Interact_Implementation()
{
	Super::Interact_Implementation();

	if (closed)
	{
		DrawerTimeline->PlayFromStart();
	}
	else
	{
		DrawerTimeline->ReverseFromEnd();
	}
	closed = !closed;
}

void AInteractiveDeskDrawer::Test(float val)
{
	ItemMesh->SetRelativeLocation(FVector(UKismetMathLibrary::Ease(0, 30, val, EEasingFunc::SinusoidalInOut), 0, 0));
}


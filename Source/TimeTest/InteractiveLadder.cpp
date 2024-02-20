// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLadder.h"
#include "Animation/AnimMontage.h"

// Sets default values
AInteractiveLadder::AInteractiveLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> animationComp(TEXT("'/Game/1-Animations/Attic_Montage.Attic_Montage'"));
	if (animationComp.Succeeded())
	{
		OpenAnim = animationComp.Object;

		SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
		SkeletalMesh->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> closedComp (TEXT("'/Game/1-Animations/attic_montage_close.attic_montage_close'"));
	if (closedComp.Succeeded())
	{
		ClosedAnim = closedComp.Object;
	}

	ItemMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void AInteractiveLadder::BeginPlay()
{
	Super::BeginPlay();

	closed = true;

	SkeletalMesh->PlayAnimation(ClosedAnim, false);

}

// Called every frame
void AInteractiveLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (closed)
	{
		ItemMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	}
	else
	{
		ItemMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	}
}

void AInteractiveLadder::Interact_Implementation()
{
	ABaseInspection::Interact_Implementation();
	if (closed)
	{
		SkeletalMesh->PlayAnimation(OpenAnim, false);
	}
	else
	{
		SkeletalMesh->PlayAnimation(ClosedAnim, false);
	}
	closed = !closed;
}


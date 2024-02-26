// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLadder.h"
#include "Animation/AnimMontage.h"

// Sets default values
AInteractiveLadder::AInteractiveLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(_rootComponent);

	ItemMesh->SetVisibility(false);

}

// Called when the game starts or when spawned
void AInteractiveLadder::BeginPlay()
{
	Super::BeginPlay();

	getOpenAnim()->bLoop = false;
	getClosedAnim()->bLoop = false;

	closed = true;

	SkeletalMesh->PlayAnimation(getClosedAnim(), false);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	SkeletalMesh->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &AInteractiveLadder::OnEnd);
}

// Called every frame
void AInteractiveLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (closed)
	{
		ItemMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	}
}

void AInteractiveLadder::OnEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ENDED!!"));
	IsActive = false;

	ItemMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
}

void AInteractiveLadder::Interact_Implementation()
{
	ABaseInspection::Interact_Implementation();
	if (!IsActive)
	{
		if (closed)
		{
			PlayAnimMontage(getOpenAnim(), 1, NAME_None);

			IsActive = true;
		}
		else
		{
			PlayAnimMontage(getClosedAnim(), 1, NAME_None);
			IsActive = true;
		}
		closed = !closed;
	}
}

float AInteractiveLadder::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	UAnimInstance* AnimInstance = (SkeletalMesh) ? SkeletalMesh->GetAnimInstance() : nullptr;
	if (AnimMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

		if (Duration > 0.f)
		{
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}

			return Duration;
		}
	}

	return 0.f;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInspection.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseInspection::ABaseInspection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _rootComponent;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetAutoActivate(false);
	AudioComponent->SetupAttachment(RootComponent);

	/*
	// audio
	static ConstructorHelpers::FObjectFinder<USoundBase> rockSound(TEXT("/Game/Audio/RockSmash.RockSmash"));
	if (rockSound.Succeeded())
	{
		throwSound = rockSound.Object;
	}*/
}

// Called when the game starts or when spawned
void ABaseInspection::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseInspection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInspection::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();

	// Play sound cues here
	float volumeMultiplier = 0.5f;

	if (PlaySound && !AudioComponent->IsPlaying())
	{
		AudioComponent->SetSound(PlaySound);
		AudioComponent->Play();
	}
}


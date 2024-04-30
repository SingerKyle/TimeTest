// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeTestCharacter.h"

//#include "AssetSelection.h"
#include "TimeTestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InspectItem.h"
#include "SaveGameInstance.h"
#include "Engine/PointLight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// ATimeTestCharacter

ATimeTestCharacter::ATimeTestCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	isFlipped = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm_Camera"));
	SpringArm->SetupAttachment(FirstPersonCameraComponent);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(SpringArm);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	
	cameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera"));
	cameraMesh->SetupAttachment(Mesh1P, "hand_r_camera");
	cameraMesh->SetRelativeScale3D(FVector(8.2, 6.3, 6.2));
	

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Timeglass Root"));
	SceneComponent->SetRelativeLocation(FVector(cameraMesh->GetRelativeLocation().X, cameraMesh->GetRelativeLocation().Y, -10000.0f));
	SceneComponent->SetupAttachment(cameraMesh);

	// Attach camera view to character.
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Timeglass Component"));
	SceneCaptureComponent->SetupAttachment(SceneComponent);
	SceneCaptureComponent->SetRelativeLocation(FVector(cameraMesh->GetRelativeLocation().X, cameraMesh->GetRelativeLocation().Y, 0));	

	// Create Plane Mesh Component
	PlaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshAsset(TEXT("'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (PlaneMeshAsset.Succeeded())
	{
		PlaneMeshComponent->SetStaticMesh(PlaneMeshAsset.Object);
	}
	PlaneMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	PlaneMeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	PlaneMeshComponent->SetRelativeScale3D(FVector(0.1, 0.05, 0.05));
	PlaneMeshComponent->SetupAttachment(cameraMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> placeholder(TEXT("'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (placeholder.Succeeded())
	{
		UStaticMesh* testmesh = placeholder.Object;
		InspectItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inspect Item"));
		InspectItem->SetStaticMesh(testmesh);
		InspectItem->SetRelativeLocation(FVector(20, 0, 0));
		InspectItem->SetRelativeScale3D(FVector(.15, .15, .15));
		InspectItem->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		InspectItem->SetupAttachment(GetFirstPersonCameraComponent());
		Item = InspectItem;
	}

	isViewingItem = false;
	LightCull = true;

	SanityComponent = CreateDefaultSubobject<USanityMeter>(TEXT("Sanity Meter"));
	AddOwnedComponent(SanityComponent);

	Sensitivity = FVector2D(1, 1);

}

void ATimeTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	InspectItem = getStaticMesh();
	if (InspectItem)
	{
		InspectItem->SetVisibility(false);
		InspectItem->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATimeTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isViewingItem && GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		InspectItem = getStaticMesh();
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		FVector2D Mouse;
		controller->GetInputMouseDelta(Mouse.X, Mouse.Y);
		//FRotator temp(InspectItem->GetRelativeRotation().Pitch + Mouse.Y * 5.0f, InspectItem->GetRelativeRotation().Yaw + Mouse.X * 5.0f, InspectItem->GetRelativeRotation().Roll);
		FRotator temp(0, -Mouse.X * 1.5, -Mouse.Y * 1.5);
		
		//InspectItem->SetRelativeRotation(temp);	
		InspectItem->AddWorldRotation(temp);
	}

	timer += DeltaTime;

	if (LightCull)
	{
		if (timer >= 0.5f)
		{
			TArray<AActor*> Lights;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALight::StaticClass(), Lights);

			for (AActor* LightActor : Lights)
			{
				ALight* light = Cast<ALight>(LightActor);

				float distance = FVector::Dist(GetActorLocation(), light->GetActorLocation());
				float OtherDistance = FVector::Dist(SceneCaptureComponent->GetComponentLocation(), light->GetActorLocation());

				if (distance > 2250 && OtherDistance > 2250)
				{
					light->SetEnabled(false);
				}
				else
				{
					light->SetEnabled(true);
				}
			}
		}
	}

	if (SanityComponent->curParanoia > 95)
	{
		//GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void ATimeTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimeTestCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATimeTestCharacter::Look);

		//PlayerInputComponent->BindAction("ShiftTime", IE_Pressed, this, &ATimeTestCharacter::ShiftTimes);
		PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATimeTestCharacter::Interact);
		PlayerInputComponent->BindAction("Save", IE_Pressed, this, &ATimeTestCharacter::Save);
		PlayerInputComponent->BindAction("Load", IE_Pressed, this, &ATimeTestCharacter::Load);
	}
}

void ATimeTestCharacter::UpdateCapture()
{
	SceneCaptureComponent->SetRelativeRotation(FirstPersonCameraComponent->GetRelativeRotation());
}

void ATimeTestCharacter::ShiftTimes()
{
	isFlipped = !isFlipped;
	SetActorTransform(SceneComponent->GetComponentTransform());

	if (isFlipped)
	{
		SceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 5000));
	}
	else
	{
		SceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -5000));
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}

void ATimeTestCharacter::Interact()
{
	if(IsViewingLock)
	{
		return;
	}

	InspectItem = getStaticMesh();
	if (isViewingItem)
	{
		ViewingItem();
		return;
	}

	FHitResult OutHit;
	FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector End = Start + GetFirstPersonCameraComponent()->GetForwardVector() * 1000;

	if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility))
	{
		// Draw line from start to hit location
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 1.0f);

		// Optionally, draw point at hit location
		//DrawDebugPoint(GetWorld(), OutHit.Location, 10.0f, FColor::Red, false, 2.0f);

		ABaseInspection* item = Cast<ABaseInspection>(OutHit.GetActor());
		if (item)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("test!"));
			item->Interact_Implementation();

			if (InspectItem && item->getInteractive() == true)
			{
				InspectItem->SetStaticMesh(item->ItemMesh->GetStaticMesh());
				InspectItem->SetRelativeScale3D(item->ItemMesh->GetRelativeScale3D() / 2);
				ViewingItem();
			}

		}
		FHitResult OutHit2;
		Start = FVector(FirstPersonCameraComponent->GetComponentLocation().X, FirstPersonCameraComponent->GetComponentLocation().Y, FirstPersonCameraComponent->GetComponentLocation().Z - 5000.f);
		End = Start + FirstPersonCameraComponent->GetForwardVector() * 1000;
		
		//GEngine->AddOnScreenDebugMessage(5, 3, FColor::Blue, FString::Printf(TEXT("Axis - %f %f %f"), OutHit2.Location.X, OutHit2.Location.Y, OutHit2.Location.Z));

		if (GetWorld()->LineTraceSingleByChannel(OutHit2, Start, End, ECC_Visibility))
		{

			// Draw line from start to hit location
			//DrawDebugLine(GetWorld(), Start, End + 5, FColor::Green, false, 2.0f, 0, 1.0f);

			// Optionally, draw point at hit location
			//DrawDebugPoint(GetWorld(), OutHit2.Location, 10.0f, FColor::Red, false, 2.0f);

			item = Cast<ABaseInspection>(OutHit2.GetActor());

			if (item)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("test!"));
				item->Interact_Implementation();
			}
		}
	}
}

void ATimeTestCharacter::Save()
{
	USaveGameInstance* saveGame = Cast<USaveGameInstance>(GetGameInstance());
	if (saveGame)
	{
		saveGame->SaveGame();
	}
}

void ATimeTestCharacter::Load()
{
	USaveGameInstance* saveGame = Cast<USaveGameInstance>(GetGameInstance());
	if (saveGame)
	{
		saveGame->LoadGame();
	}
}

void ATimeTestCharacter::ToggleLightingCull()
{
	LightCull = !LightCull;

	if(!LightCull)
	{
		TArray<AActor*> Lights;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALight::StaticClass(), Lights);

		for (AActor* LightActor : Lights)
		{
			ALight* light = Cast<ALight>(LightActor);

			light->SetEnabled(true);

		}
	}
}

void ATimeTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATimeTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !isViewingItem) 
	{
		if(!IsViewingLock)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X * Sensitivity.X);
			AddControllerPitchInput(LookAxisVector.Y * Sensitivity.Y);

			UpdateCapture();
		}
	}
}

void ATimeTestCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATimeTestCharacter::GetHasRifle()
{
	return bHasRifle;
}

void ATimeTestCharacter::ViewingItem()
{
	if (!isViewingItem)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		InspectItem->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh1P()->ToggleVisibility(true);
		InspectItem->SetVisibility(true);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		GetMesh1P()->ToggleVisibility(true);
		InspectItem->SetVisibility(false);
	}

	isViewingItem = !isViewingItem;
}

// Functions to allow the player to save and load game state

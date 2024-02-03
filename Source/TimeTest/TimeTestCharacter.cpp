// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeTestCharacter.h"
#include "TimeTestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CameraMesh(TEXT("'/Game/Assets/SM_Camera02.SM_Camera02'"));
	if (CameraMesh.Succeeded())
	{
		UStaticMesh* camMesh = CameraMesh.Object;
		cameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
		cameraMesh->SetStaticMesh(camMesh);
		cameraMesh->SetupAttachment(Mesh1P, "hand_r_camera");
		//cameraMesh->SetRelativeLocation(FVector(40, 0, -20));
		cameraMesh->SetRelativeRotation(FRotator(0,90,0));
	}

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Timeglass Root"));
	SceneComponent->SetRelativeLocation(FVector(cameraMesh->GetRelativeLocation().X, cameraMesh->GetRelativeLocation().Y, -5000.0f));
	SceneComponent->SetupAttachment(GetCapsuleComponent());

	// Attach camera view to character.
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Timeglass Component"));
	SceneCaptureComponent->SetupAttachment(SceneComponent);

	// Create Plane Mesh Component
	PlaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshAsset(TEXT("'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (PlaneMeshAsset.Succeeded())
	{
		PlaneMeshComponent->SetStaticMesh(PlaneMeshAsset.Object);
	}
	//PlaneMeshComponent->SetRelativeLocation(FVector(41.0f, -20.0f, -10.0f));
	//PlaneMeshComponent->SetRelativeRotation(FRotator(0.0f, 60.0f, 90.0f));
	//PlaneMeshComponent->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
	PlaneMeshComponent->SetRelativeLocation(FVector(0.0f, -10.0f, 0.0f));
	PlaneMeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	PlaneMeshComponent->SetRelativeScale3D(FVector(0.1, 0.05, 0.05));
	PlaneMeshComponent->SetupAttachment(cameraMesh);
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

		PlayerInputComponent->BindAction("ShiftTime", IE_Pressed, this, &ATimeTestCharacter::ShiftTimes);
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

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
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

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		UpdateCapture();
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
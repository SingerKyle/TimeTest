// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameSaveSystem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SanityMeter.h"
#include "TimeTestCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;


UCLASS(config = Game)
class ATimeTestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Shift Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ShiftTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Capture", meta = (AllowPrivateAccess = "true")) class USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* PlaneMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components") USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true")); UStaticMeshComponent* cameraMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes", meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* InspectItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sanity Bar", meta = (AllowPrivateAccess = "true")) TObjectPtr<USanityMeter> SanityComponent;

	TObjectPtr<UStaticMeshComponent> Item;

	UPROPERTY(VisibleAnywhere) USpringArmComponent* SpringArm;

	float timer = 0;
public:
	ATimeTestCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Category = "Interaction") void ViewingItem();

private:
	// Mouse Sensitivity Options :)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) FVector2D Sensitivity;
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	virtual void UpdateCapture();

	UFUNCTION() UStaticMeshComponent* getStaticMesh()
	{
		return Item;
	}

	virtual void ShiftTimes();
	void Interact();
	void Save();
	void Load();

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	UFUNCTION(BlueprintCallable, Category = "Lighting Cull") void ToggleLightingCull();

	bool isFlipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isViewingItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool LightCull;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsViewingLock;
};


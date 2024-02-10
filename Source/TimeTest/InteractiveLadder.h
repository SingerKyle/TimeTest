// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInspection.h"
#include "GameFramework/Actor.h"
#include "InteractiveLadder.generated.h"

UCLASS()
class TIMETEST_API AInteractiveLadder : public ABaseInspection
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveLadder();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool closed;

	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UAnimMontage* OpenAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UAnimMontage* ClosedAnim;
};

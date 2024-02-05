// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionInterface.h"

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.
void Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Interacting!"));
}
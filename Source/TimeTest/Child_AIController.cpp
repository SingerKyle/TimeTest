// Fill out your copyright notice in the Description page of Project Settings.


#include "Child_AIController.h"
#include "GhostChild.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AChild_AIController::AChild_AIController(const FObjectInitializer& ObjectInitializer)
{

}

void AChild_AIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	if (AGhostChild* const child = Cast<AGhostChild>(inPawn))
	{
		if (UBehaviorTree* const tree = child->getBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

void AChild_AIController::initPerception()
{

}

void AChild_AIController::onTargetInSight(AActor* actor, FAIStimulus const Stimulus)
{

}

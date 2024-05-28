// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controllers/AIBaseController.h"
#include "Rapid/RapidCharacter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"


AAIBaseController::AAIBaseController()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void AAIBaseController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AAIBaseController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AIPerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &ThisClass::OnTargetPerceptionUpdated);

	Super::EndPlay(EndPlayReason);
}

void AAIBaseController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	if (Stimulus.WasSuccessfullySensed())
	{
		BlackboardComponent->SetValueAsObject(TargetActorBlackboardKey, Actor);
	}
	else
	{
		if (const AActor* TargetedActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorBlackboardKey));
			TargetedActor == Actor)
		{
			BlackboardComponent->SetValueAsObject(TargetActorBlackboardKey, nullptr);
		}
	}
}

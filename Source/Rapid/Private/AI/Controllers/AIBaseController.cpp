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

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);
}

void AAIBaseController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AIPerceptionComponent->OnPerceptionUpdated.RemoveDynamic(this, &ThisClass::OnPerceptionUpdated);

	Super::EndPlay(EndPlayReason);
}

void AAIBaseController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	for (AActor* UpdatedActor : UpdatedActors)
	{
		//TODO
		//add team affiliation 
		if (Cast<ARapidCharacter>(UpdatedActor))
		{
			BlackboardComponent->SetValueAsObject(TargetActorBlackboardKey, UpdatedActor);
		}
	}
}

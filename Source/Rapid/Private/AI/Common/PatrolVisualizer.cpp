// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/PatrolVisualizer.h"
#include "Components/SphereComponent.h"

void FPatrolVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                          FPrimitiveDrawInterface* PDI)
{
	//TODO
	if (const USphereComponent* SphereComponent = Cast<USphereComponent>(Component))
	{
		DrawWireSphere(PDI, SphereComponent->GetComponentLocation(), FColor::Blue,
		               SphereComponent->GetScaledSphereRadius(), 16, SDPG_World);
	}
}

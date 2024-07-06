// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ComponentVisualizer.h"

/**
 * 
 */
class RAPID_API FPatrolVisualizer final : public FComponentVisualizer
{
public:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	                               FPrimitiveDrawInterface* PDI) override;
};

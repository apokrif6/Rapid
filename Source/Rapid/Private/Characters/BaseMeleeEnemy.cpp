// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMeleeEnemy.h"
#include "Combat/Components/MeleeWeaponTraceComponent.h"

ABaseMeleeEnemy::ABaseMeleeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	MeleeWeaponTraceComponent = CreateDefaultSubobject<UMeleeWeaponTraceComponent>("MeleeWeaponTraceComponent");
}

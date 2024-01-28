
// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerableActors/GGJ_TriggerableActor.h"
#include "Characters/GGJ_BaseCharacter.h"

AGGJ_TriggerableActor::AGGJ_TriggerableActor()
{
	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	MainMeshComponent->SetupAttachment(RootComponent);

	SetActorHiddenInGame(false);
}

void AGGJ_TriggerableActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AGGJ_BaseCharacter* OtherCharacter = Cast<AGGJ_BaseCharacter>(OtherActor);
	if (OtherCharacter) {
		BP_OnCharacterBeginOverlap(OtherCharacter);
	}
}

void AGGJ_TriggerableActor::ChangeVisibility(const bool bVisible)
{
	SetActorHiddenInGame(!bVisible);
	SetActorEnableCollision(bVisible);
}

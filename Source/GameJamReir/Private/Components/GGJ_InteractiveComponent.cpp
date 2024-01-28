// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GGJ_InteractiveComponent.h"

UGGJ_InteractiveComponent::UGGJ_InteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bCanBeUsed = true;
	bCanOnlyBeUsedOnce = true;
}

void UGGJ_InteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGGJ_InteractiveComponent::SetCanBeUsed(const bool bState)
{
	if (bCanBeUsed != bState) {
		bCanBeUsed = bState;
		OnCanBeUsedChangedDelegate.Broadcast(bCanBeUsed);
	}
}

bool UGGJ_InteractiveComponent::CanUseInteraction(const APawn* InteractionInstigator) const
{
	return bCanBeUsed;
}

void UGGJ_InteractiveComponent::TriggerInteraction(APawn* InteractionInstigator)
{
	if (bCanBeUsed && bCanOnlyBeUsedOnce) {
		SetCanBeUsed(false);
		OnInteractionTriggeredDelegate.Broadcast(InteractionInstigator);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActors/GGJ_InteractiveActor.h"
#include "Components/GGJ_InteractiveComponent.h"
#include "Components/WidgetComponent.h"

AGGJ_InteractiveActor::AGGJ_InteractiveActor()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractiveComponent = CreateDefaultSubobject<UGGJ_InteractiveComponent>(TEXT("InteractiveComponent"));

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidgetComponent"));
	InteractionWidgetComponent->SetupAttachment(RootComponent);
}

void AGGJ_InteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (InteractiveComponent) {
		InteractiveComponent->OnCanBeUsedChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnCanBeUsedChanged);
		InteractionWidgetComponent->SetVisibility(InteractiveComponent->CanBeUsed());
	}
}

void AGGJ_InteractiveActor::OnCanBeUsedChanged(const bool bNewState)
{
	InteractionWidgetComponent->SetVisibility(bNewState);
}

bool AGGJ_InteractiveActor::BP_CanUseInteraction_Implementation(const APawn* InteractionInstigator) const
{
	return InteractiveComponent? InteractiveComponent->CanUseInteraction(InteractionInstigator) : false;
}

FText AGGJ_InteractiveActor::BP_GetInteractionText_Implementation(const APawn* InteractionInstigator) const
{
	return InteractiveComponent ? InteractiveComponent->GetInteractionText(InteractionInstigator) : FText();
}

void AGGJ_InteractiveActor::BP_TriggerInteraction_Implementation(APawn* InteractionInstigator)
{
	if (InteractiveComponent) {
		InteractiveComponent->TriggerInteraction(InteractionInstigator);
	}
}

UGGJ_InteractiveComponent* AGGJ_InteractiveActor::BP_GetInteractiveComponent_Implementation() const
{
	return InteractiveComponent;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GGJ_InteractionComponent.h"
#include "InteractiveActors/GGJ_InteractiveActorInterface.h"
#include "GGJ_Definitions.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"

UGGJ_InteractionComponent::UGGJ_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bDefaultCanUseInteractions = true;
	TickInteractionRate = 0.3f;
	InteractionRadious = 50.f;
	MaxDistanceInteraction = 200.f;
}

void UGGJ_InteractionComponent::TryTriggerInteraction()
{
	if (OwnerPawnPtr.IsValid() && InteractingWithActorPtr.IsValid() &&
		InteractingWithActorPtr->Implements<UGGJ_InteractiveActorInterface>() &&
		IGGJ_InteractiveActorInterface::Execute_BP_CanUseInteraction(InteractingWithActorPtr.Get(), OwnerPawnPtr.Get())) {
		IGGJ_InteractiveActorInterface::Execute_BP_TriggerInteraction(InteractingWithActorPtr.Get(), OwnerPawnPtr.Get());
	}
}

void UGGJ_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawnPtr = Cast<APawn>(GetOwner());
	SetCanUseInteractions(bDefaultCanUseInteractions);
}

void UGGJ_InteractionComponent::SetCanUseInteractions(const bool bNewValue)
{
	if (bNewValue != bCanUseInteractions) {
		bCanUseInteractions = bNewValue;

		if (bCanUseInteractions) {
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_TickInteraction, this, &ThisClass::TickInteraction, TickInteractionRate, true);
		}
		else {
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_TickInteraction);
		}

		SetInteractingWithActor(nullptr);
	}
}

void UGGJ_InteractionComponent::TickInteraction()
{
	if (!OwnerPawnPtr.IsValid()) {
		return;
	}

	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerPawnPtr->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector AimDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (AimDirection * MaxDistanceInteraction);

	TArray<AActor*> IgnoreActors = { Cast<AActor>(this)};

	FHitResult HitResult;
	AActor* NewTargetActor = nullptr;

	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), EyeLocation, TraceEnd, InteractionRadious, 
		UEngineTypes::ConvertToTraceType(ECC_Interaction), false, IgnoreActors, EDrawDebugTrace::None, HitResult, true)) {
		AActor* HitActor = HitResult.GetActor();
		if (HitActor &&
			HitActor->Implements<UGGJ_InteractiveActorInterface>() &&
			IGGJ_InteractiveActorInterface::Execute_BP_CanUseInteraction(HitActor, OwnerPawnPtr.Get())) {
			NewTargetActor = HitActor;
		}
	}

	SetInteractingWithActor(NewTargetActor);
}

void UGGJ_InteractionComponent::SetInteractingWithActor(AActor* NewActor)
{
	if (NewActor != InteractingWithActorPtr) {
		if (InteractingWithActorPtr.IsValid()) {
			OnStoppedInteractingWithActorDelegate.Broadcast(InteractingWithActorPtr.Get());
		}

		InteractingWithActorPtr = NewActor;

		if (NewActor) {
			OnStartedInteractingWithActorDelegate.Broadcast(NewActor);
		}
	}
}


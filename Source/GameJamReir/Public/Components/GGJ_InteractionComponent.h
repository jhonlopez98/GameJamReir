// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGJ_InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGGJ_OnInteractionEventSignature, AActor*, OtherActor);

/**
 * Component used for any actor that can use interactions
 * Can only interact with one object at a time
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAMREIR_API UGGJ_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<APawn> OwnerPawnPtr;

	TWeakObjectPtr<AActor> InteractingWithActorPtr;

	UPROPERTY(EditDefaultsOnly)
	uint8 bDefaultCanUseInteractions : 1;

	uint8 bCanUseInteractions : 1;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = bCanUseInteractions))
	float TickInteractionRate;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = bCanUseInteractions))
	float InteractionRadious;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = bCanUseInteractions))
	float MaxDistanceInteraction;

	FTimerHandle TimerHandle_TickInteraction;

	virtual void BeginPlay() override;

	void SetCanUseInteractions(const bool bNewValue);

	UFUNCTION()
	void TickInteraction();

	void SetInteractingWithActor(AActor* NewActor);

public:
	UPROPERTY(BlueprintAssignable)
	FGGJ_OnInteractionEventSignature OnStartedInteractingWithActorDelegate;

	UPROPERTY(BlueprintAssignable)
	FGGJ_OnInteractionEventSignature OnStoppedInteractingWithActorDelegate;

	UGGJ_InteractionComponent();

	void TryTriggerInteraction();
};

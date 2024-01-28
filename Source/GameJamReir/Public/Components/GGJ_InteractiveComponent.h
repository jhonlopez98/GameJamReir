// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGJ_InteractiveComponent.generated.h"

class UGGJ_InteractiveComponent;
class APawn;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FGGJ_InteractionTriggeredSignature, UGGJ_InteractiveComponent, OnInteractionTriggeredDelegate, APawn*, InteractionInstigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGGJ_OnCanBeUsedChangedSignature, const bool, bState);

/**
 * Component for any actor that is interactive
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAMREIR_API UGGJ_InteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	FText InteractionText;

	UPROPERTY(EditDefaultsOnly)
	uint8 bCanBeUsed : 1;

	UPROPERTY(EditDefaultsOnly)

	uint8 bCanOnlyBeUsedOnce : 1;

	virtual void BeginPlay() override;

	void SetCanBeUsed(const bool bState);

public:
	UPROPERTY(BlueprintAssignable)
	FGGJ_OnCanBeUsedChangedSignature OnCanBeUsedChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FGGJ_InteractionTriggeredSignature OnInteractionTriggeredDelegate;

	UGGJ_InteractiveComponent();

	bool CanBeUsed() const { return bCanBeUsed; }

	bool CanUseInteraction(const APawn* InteractionInstigator) const;

	const FText& GetInteractionText(const APawn* InteractionInstigator) const { return InteractionText; }

	void TriggerInteraction(APawn* InteractionInstigator);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ_InteractiveActorInterface.h"
#include "GGJ_InteractiveActor.generated.h"

class UGGJ_InteractiveComponent;
class UWidgetComponent;

/**
 * Base class for an actor that is interactive 
 */
UCLASS()
class GAMEJAMREIR_API AGGJ_InteractiveActor : public AActor, public IGGJ_InteractiveActorInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UGGJ_InteractiveComponent> InteractiveComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCanBeUsedChanged(const bool bNewState);

public:
	AGGJ_InteractiveActor();

#pragma region IGGJ_InteractiveActorInterface
public:
	bool BP_CanUseInteraction_Implementation(const APawn* InteractionInstigator) const override;
	FText BP_GetInteractionText_Implementation(const APawn* InteractionInstigator) const override;
	void BP_TriggerInteraction_Implementation(APawn* InteractionInstigator) override;
	UGGJ_InteractiveComponent* BP_GetInteractiveComponent_Implementation() const override;
#pragma endregion IGGJ_InteractiveActorInterface
};

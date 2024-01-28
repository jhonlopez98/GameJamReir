// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGJ_InteractiveActorInterface.generated.h"

class UGGJ_InteractiveComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGGJ_InteractiveActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for any actor that the character can interact with
 */
class GAMEJAMREIR_API IGGJ_InteractiveActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = InteractiveActorInterface)
	bool BP_CanUseInteraction(const APawn* InteractionInstigator) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = InteractiveActorInterface)
	FText BP_GetInteractionText(const APawn* InteractionInstigator) const;

	UFUNCTION(BlueprintNativeEvent, Category = InteractiveActorInterface)
	void BP_TriggerInteraction(APawn* InteractionInstigator);

	UFUNCTION(BlueprintNativeEvent, Category = InteractiveActorInterface)
	UGGJ_InteractiveComponent* BP_GetInteractiveComponent() const;
};

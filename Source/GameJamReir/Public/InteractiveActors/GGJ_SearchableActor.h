// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActors/GGJ_InteractiveActor.h"
#include "GameplayTagContainer.h"
#include "GGJ_SearchableActor.generated.h"

class AGGJ_BaseCharacter;
class UStaticMeshComponent;

/**
 * Actors in the map where the player can search items
 */
UCLASS()
class GAMEJAMREIR_API AGGJ_SearchableActor : public AGGJ_InteractiveActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	/** Gameplay tags that this actor can reward*/
	UPROPERTY(VisibleAnywhere, Category = Reward)
	TArray<FGameplayTag> PossibleRewardTags;

public:
	AGGJ_SearchableActor();

	void OverridePossibleRewardTags(const TArray<FGameplayTag>& NewPossibleReward);

	UFUNCTION(BlueprintCallable)
	void GiveRandomReward(AGGJ_BaseCharacter* Character);
};

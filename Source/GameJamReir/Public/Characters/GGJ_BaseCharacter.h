// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "GGJ_BaseCharacter.generated.h"

class UGGJ_InteractionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGGJ_OnGameplayTagsChangedSignature, const FGameplayTag&, Tag, const bool, bAdded);

/** 
 * Base class for any character
 */
UCLASS()
class GAMEJAMREIR_API AGGJ_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UGGJ_InteractionComponent> InteractionComponent;

	UPROPERTY(BlueprintReadOnly, Category = Tags)
	FGameplayTagContainer GameplayTagContainer;

	virtual void BeginPlay() override;

	/** If currently interacting with an object trigger interaction*/
	UFUNCTION(BlueprintCallable)
	void TryTriggerInteraction();

	/** 
	 * Called when the gameplay tags in this character changed
	 * @param Tag that changed
	 * @param bAdded True if added, False if removed
	 */
	void OnGameplayTagsChanged(const FGameplayTag& Tag, const bool bAdded);

public:
	UPROPERTY(BlueprintAssignable)
	FGGJ_OnGameplayTagsChangedSignature OnGameplayTagsChangedDelegate;

	AGGJ_BaseCharacter();

	UFUNCTION(BlueprintCallable, Category = Tags, meta = (AutoCreateRefTerm = "Tag"))
	void AddGameplayTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = Tags, meta = (AutoCreateRefTerm = "Tag"))
	void RemoveGameplayTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = Tags, meta = (AutoCreateRefTerm = "Tag"))
	bool HasGameplayTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = Tags, meta = (AutoCreateRefTerm = "Tag"))
	bool HasGameplayTagExact(const FGameplayTag& Tag);
};

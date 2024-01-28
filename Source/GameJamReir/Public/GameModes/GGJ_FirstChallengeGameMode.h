// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include "GGJ_FirstChallengeGameMode.generated.h"

class AGGJ_TriggerableActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGGJ_OnMatchEventSignature);

/**
 * Game mode for the first challenge
 */
UCLASS()
class GAMEJAMREIR_API AGGJ_FirstChallengeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	/** Gameplay tags that the character must have to win*/
	UPROPERTY(EditDefaultsOnly, Category = Rules)
	TArray<FGameplayTag> CharacterWinTags;

	/** Gameplay tags that character must have to reset*/
	UPROPERTY(EditDefaultsOnly, Category = Rules)
	TArray<FGameplayTag> CharacterResetTags;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGGJ_TriggerableActor> PortalsClass;

	TArray<TWeakObjectPtr<AGGJ_TriggerableActor>> PortalPtrs;

	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FGGJ_OnMatchEventSignature OnPortalsActivatedDelegate;

	UPROPERTY(BlueprintAssignable)
	FGGJ_OnMatchEventSignature OnCharacterResetDelegate;

	AGGJ_FirstChallengeGameMode();

	void SetupWinRewards();

	void SetupPortals();

	void OnCharacterGameplayTagAdded(ACharacter* Character, const FGameplayTag& TagAdded, const FGameplayTagContainer& CharacterTags);

	void ActivatePortals();

	void SendCharacterToResetPoint(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SendCharacterToResetPoint(ACharacter* Character);
};

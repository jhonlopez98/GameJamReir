// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GGJ_BaseCharacter.h"
#include "Components/GGJ_InteractionComponent.h"
#include "GameModes/GGJ_FirstChallengeGameMode.h"

AGGJ_BaseCharacter::AGGJ_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionComponent = CreateDefaultSubobject<UGGJ_InteractionComponent>(TEXT("InteractionComponent"));
}

void AGGJ_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AGGJ_BaseCharacter::TryTriggerInteraction()
{
	if (InteractionComponent) {
		InteractionComponent->TryTriggerInteraction();
	}
}

void AGGJ_BaseCharacter::OnGameplayTagsChanged(const FGameplayTag& Tag, const bool bAdded)
{
	if (bAdded) {
		AGGJ_FirstChallengeGameMode* FirstChallengeGameMode = GetWorld()->GetAuthGameMode<AGGJ_FirstChallengeGameMode>();
		if (FirstChallengeGameMode) {
			FirstChallengeGameMode->OnCharacterGameplayTagAdded(this, Tag, GameplayTagContainer);
		}
	}

	OnGameplayTagsChangedDelegate.Broadcast(Tag, bAdded);
}

void AGGJ_BaseCharacter::AddGameplayTag(const FGameplayTag& Tag)
{
	if (!GameplayTagContainer.HasTag(Tag)) {
		GameplayTagContainer.AddTag(Tag);
		OnGameplayTagsChanged(Tag, true);
	}
}

void AGGJ_BaseCharacter::RemoveGameplayTag(const FGameplayTag& Tag)
{
	const bool bRemoved = GameplayTagContainer.RemoveTag(Tag);
	if (bRemoved) {
		OnGameplayTagsChanged(Tag, false);
	}
}

bool AGGJ_BaseCharacter::HasGameplayTag(const FGameplayTag& Tag)
{
	return GameplayTagContainer.HasTag(Tag);
}

bool AGGJ_BaseCharacter::HasGameplayTagExact(const FGameplayTag& Tag)
{
	return GameplayTagContainer.HasTagExact(Tag);
}


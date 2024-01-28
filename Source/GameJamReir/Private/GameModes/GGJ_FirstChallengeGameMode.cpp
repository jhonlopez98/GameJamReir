// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GGJ_FirstChallengeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "InteractiveActors/GGJ_SearchableActor.h"
#include "TriggerableActors/GGJ_TriggerableActor.h"

AGGJ_FirstChallengeGameMode::AGGJ_FirstChallengeGameMode()
{
	
}

void AGGJ_FirstChallengeGameMode::BeginPlay()
{
	SetupWinRewards();
	SetupPortals();
}

void AGGJ_FirstChallengeGameMode::SetupWinRewards()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGGJ_SearchableActor::StaticClass(), FoundActors);

	const int32 NumWinTags = CharacterWinTags.Num();

	if (FoundActors.Num() < NumWinTags) {
		UE_LOG(LogTemp, Error, TEXT("The map has no enough SearchableActors to place all the win rewards"));
		return;
	}

	TArray<AGGJ_SearchableActor*> SelectedSearchableActors;

	if (FoundActors.Num() == NumWinTags) {
		for (AActor* FoundActor : FoundActors)
		{
			SelectedSearchableActors.Add(Cast<AGGJ_SearchableActor>(FoundActor));
		}
	}
	else {
		while (SelectedSearchableActors.Num() < NumWinTags)
		{
			const int32 RandomIndex = FMath::RandRange(0, FoundActors.Num() - 1);
			AGGJ_SearchableActor* SelectedSearchableActor = Cast<AGGJ_SearchableActor>(FoundActors[RandomIndex]);

			if (SelectedSearchableActor && !SelectedSearchableActors.Contains(SelectedSearchableActor)) {
				SelectedSearchableActors.Add(SelectedSearchableActor);
			}
		}
	}

	int32 Index = 0;
	for (AGGJ_SearchableActor* SelectedSearchable : SelectedSearchableActors)
	{
		if (SelectedSearchable) {
			SelectedSearchable->OverridePossibleRewardTags({ CharacterWinTags[Index] });
			Index++;
		}
	}
}

void AGGJ_FirstChallengeGameMode::SetupPortals()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PortalsClass, FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		AGGJ_TriggerableActor* FoundPortal = Cast<AGGJ_TriggerableActor>(FoundActor);
		if (FoundPortal) {
			FoundPortal->ChangeVisibility(false);
			PortalPtrs.Add(FoundPortal);
		}
	}
}

void AGGJ_FirstChallengeGameMode::OnCharacterGameplayTagAdded(ACharacter* Character, const FGameplayTag& TagAdded, const FGameplayTagContainer& CharacterTags)
{
	if (CharacterWinTags.Contains(TagAdded)) {
		bool bWinCondition = true;
		for (const FGameplayTag& Tag : CharacterWinTags)
		{
			if (!CharacterTags.HasTag(Tag)) {
				bWinCondition = false;
				break;
			}
		}

		if (bWinCondition) {
			ActivatePortals();
			return;
		}
	}

	if (CharacterResetTags.Contains(TagAdded)) {
		bool bResetCondition = true;
		for (const FGameplayTag& Tag : CharacterResetTags)
		{
			if (!CharacterTags.HasTag(Tag)) {
				bResetCondition = false;
				break;
			}
		}

		if (bResetCondition) {
			SendCharacterToResetPoint(Character);
			return;
		}
	}
}

void AGGJ_FirstChallengeGameMode::ActivatePortals()
{
	for (const TWeakObjectPtr<AGGJ_TriggerableActor>& PortalPtr : PortalPtrs)
	{
		if (PortalPtr.IsValid()) {
			PortalPtr->ChangeVisibility(true);
		}
	}
	OnPortalsActivatedDelegate.Broadcast();
}

void AGGJ_FirstChallengeGameMode::SendCharacterToResetPoint(ACharacter* Character)
{
	OnCharacterResetDelegate.Broadcast();
	BP_SendCharacterToResetPoint(Character);
}

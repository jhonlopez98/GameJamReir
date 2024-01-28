// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActors/GGJ_SearchableActor.h"
#include "GGJ_Definitions.h"
#include "Characters/GGJ_BaseCharacter.h"
#include "Components/WidgetComponent.h"

AGGJ_SearchableActor::AGGJ_SearchableActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Interaction, ECollisionResponse::ECR_Block);

	InteractionWidgetComponent->SetupAttachment(StaticMeshComponent);
}

void AGGJ_SearchableActor::OverridePossibleRewardTags(const TArray<FGameplayTag>& NewPossibleReward)
{
	PossibleRewardTags = NewPossibleReward;
}

void AGGJ_SearchableActor::GiveRandomReward(AGGJ_BaseCharacter* Character)
{
	if (Character && PossibleRewardTags.Num() > 0) {
		const int32 RandomIndex = FMath::RandRange(0, PossibleRewardTags.Num() - 1);
		Character->AddGameplayTag(PossibleRewardTags[RandomIndex]);
	}
}

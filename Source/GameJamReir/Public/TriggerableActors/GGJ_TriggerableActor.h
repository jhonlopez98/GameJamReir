// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "GGJ_TriggerableActor.generated.h"

class AGGJ_BaseCharacter;

/**
 * Base class for any actor that can be triggered by the player
 */
UCLASS()
class GAMEJAMREIR_API AGGJ_TriggerableActor : public ATriggerSphere
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UStaticMeshComponent> MainMeshComponent;

public:
	AGGJ_TriggerableActor();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnCharacterBeginOverlap(AGGJ_BaseCharacter* OtherCharacter);

	void ChangeVisibility(const bool bVisible);
};

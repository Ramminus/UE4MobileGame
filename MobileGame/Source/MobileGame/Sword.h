// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEGAME_API USword : public UWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float AttackAngle;
public:

	//Getters
	FORCEINLINE float GetAttackAngle() const { return AttackAngle;}


	//Attack Function Override
	virtual void OnAttack(UWorld* WorldContext,  AActor* AttackerActor) override;
};

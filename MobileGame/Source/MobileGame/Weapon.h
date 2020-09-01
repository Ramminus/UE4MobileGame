// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EquipmentModule.h"
#include "HealthModule.h"
#include "Item.h"
#include "Weapon.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAttack, AActor*, Actor);
/**
 * 
 */
UCLASS(Blueprintable)
class MOBILEGAME_API UWeapon : public UItem
{
	GENERATED_BODY()
public:
	UWeapon();

	//The Team of the owner the weapon belongs to.
	UPROPERTY(BlueprintReadOnly)
	ETeam OwnerTeam;
protected:
	/* The Weapon type for this weapon.*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attack Values")
	EWeaponTypes WeaponType;

	//The model for the weapon.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals")
	USkeletalMesh* Model;

	//Base Damage of the weapon.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attack Values")
	float Damage;

	//Weapon Base Attack Speed.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Attack Values")
	float AttackSpeed;
	//Attack range for the weapon.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attack Values")
	float AttackRange;

	//Delay for the attack function to be called
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float AttackDelay;

	//Montage to play at the begining of the attack.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Visuals")
	UAnimMontage* MontageToPlay;

	
public:
	//Getters
	FORCEINLINE EWeaponTypes GetWeaponType() const { return WeaponType;}
	FORCEINLINE ETeam GetOwnerTeam() const { return OwnerTeam;}
	FORCEINLINE USkeletalMesh*  GetModel()  const  {return Model;}
	FORCEINLINE float GetAttackRange() const {return AttackRange;}
	FORCEINLINE float GetDamage() const { return Damage;}
	FORCEINLINE UAnimMontage* GetMontage() const {return MontageToPlay;}
	FORCEINLINE float GetAttackSpeed()  const {return AttackSpeed;}
	FORCEINLINE float GetAttackDelay() const {return AttackDelay;}

	virtual void OnAttack(UWorld* WorldContext,  AActor* AttackerActor);
};

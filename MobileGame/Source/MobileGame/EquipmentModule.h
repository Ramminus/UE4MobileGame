// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"

#include "EquipmentModule.generated.h"


class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EWeaponTypes : uint8 {
	None = 0 UMETA(DisplayName="None"),
	Sword = 1 UMETA(DisplayName="Sword")
};
USTRUCT(BlueprintType) 
struct FWeaponData : public FTableRowBase{

	GENERATED_BODY()



public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttachedItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackAngle;

	FWeaponData() {
		AttachedItemID = -1;
	}
		



};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEGAME_API UEquipmentModule : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentModule();
	UPROPERTY(VisibleAnywhere)
		FWeaponData CurrentWeapon;
	UPROPERTY(VisibleAnywhere,  BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void EquipWeapon(FWeaponData NewWeapon);

		
};

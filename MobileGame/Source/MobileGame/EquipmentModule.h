// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"

#include "EquipmentModule.generated.h"

class UAnimMontage;
class USkeletalMeshComponent;
class UWeapon;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipWeapon);

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
	float AttackDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* MontageToPlay;
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
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(VisibleAnywhere,  BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnEquipWeapon OnEquipWeapon;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnUpdateWeapon)
		UWeapon* CurrentWeapon;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnUpdateWeapon();
	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(TSubclassOf<UWeapon> WeaponToEquip);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void EquipWeapon (TSubclassOf<UWeapon> NewWeapon);
	FORCEINLINE UWeapon* GetEquipedWeapon() const{return CurrentWeapon;}
		
};

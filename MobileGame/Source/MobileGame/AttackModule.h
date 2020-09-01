// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackModule.generated.h"

class USkeletalMeshComponent;
class UWeapon;
class UHealthModule;
class UEquipmentModule;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEGAME_API UAttackModule : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackModule();

	UPROPERTY(BlueprintReadWrite, Category="Animation")
	USkeletalMeshComponent* MontageMeshComponent;
	
protected:
	UHealthModule* HealthModule;
	UEquipmentModule* EquipmentModule;
	float AttackTimer;
	bool bHasAttacked;

	//Attack Timer Handler - used when starting an attack;
	FTimerHandle AttackTimerHandler;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	//Server implementation for Start Attack
	UFUNCTION(Server, Reliable, Category="Attack")
	void ServerOnStartAttack();

	//Multicast implementation for Start Attack
	UFUNCTION(NetMulticast, Reliable, Category="Attack")
	void MultiCastOnStartAttack();



	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void OnAttack();
	UFUNCTION(Server, Reliable)
	void ServerOnAttack();

	UFUNCTION(BlueprintCallable, Category="Attack")
	void StartAttack();
	
private:
	
	
};

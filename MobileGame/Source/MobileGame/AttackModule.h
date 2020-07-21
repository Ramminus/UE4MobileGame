// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackModule.generated.h"

class UHealthModule;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEGAME_API UAttackModule : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackModule();

protected:
	UHealthModule* HealthModule;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void OnAttack();
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthModule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageEvent, float, HealthPercentage);


UENUM()
enum class ETeam : uint8
{
	FRIENDLY     UMETA(DisplayName = "Friendly"),
	NEUTRAL      UMETA(DisplayName = "Neutral"),
	ENEMY   UMETA(DisplayName = "Enemy"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEGAME_API UHealthModule : public UActorComponent
{
	GENERATED_BODY()
	

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Sets default values for this component's properties
	UHealthModule();
	UPROPERTY(EditAnywhere)
	int MaxHealth;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTakeDamageEvent OnTakeDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDead;

protected:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_CurrentHealth)
	int CurrentHealth;
	UFUNCTION()
	void OnHealthUpodated();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OnDeath();
	bool CanDamage(ETeam thisTeam, ETeam OtherTeam);
public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int amount, ETeam thisTeam, ETeam attackersTeam);
	UFUNCTION(BlueprintCallable)
	void HealHealth(int amount);

	UFUNCTION()
	void OnRep_CurrentHealth();
};



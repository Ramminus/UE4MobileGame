// Fill out your copyright notice in the Description page of Project Settings.
#include "HealthModule.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"


void UHealthModule::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthModule, CurrentHealth);
}

// Sets default values for this component's properties
UHealthModule::UHealthModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthModule::OnHealthUpodated()
{
	float percentage = (float)CurrentHealth / (float)MaxHealth;
	OnTakeDamage.Broadcast(percentage);

	if (CurrentHealth <= 0) {
		OnDeath();
	}


	

	//Functions that occur on all machines. 
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
	
}

// Called when the game starts
void UHealthModule::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	 
	
}

void UHealthModule::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I Died!"));
	IsDead = true;
}

bool UHealthModule::CanDamage(ETeam thisTeam, ETeam OtherTeam)
{
	return (thisTeam == ETeam::NEUTRAL) || (OtherTeam != thisTeam);
}

void UHealthModule::TakeDamage(int amount, ETeam thisTeam, ETeam attackersTeam)
{
	if (!CanDamage(thisTeam, attackersTeam) || IsDead)return;
	CurrentHealth -= amount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Health is: %d"), CurrentHealth));
	OnHealthUpodated();
	
	
}

void UHealthModule::HealHealth(int amount)
{
	CurrentHealth += amount;
	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
	IsDead = CurrentHealth <= 0;
	float percentage = (float)CurrentHealth / (float)MaxHealth;
	//OnTakeDamage.Broadcast(percentage);
}

void UHealthModule::OnRep_CurrentHealth()
{
	OnHealthUpodated();
}


// Called every frame
//void UHealthModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Teamable.h"
#include "EnemyBase.generated.h"

UCLASS()
class MOBILEGAME_API AEnemyBase : public ACharacter, public ITeamable
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere)
	ETeam Team;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthModule* HealthModule; 
public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ITeamable Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Team")
	ETeam GetTeam();
	virtual ETeam GetTeam_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	class UHealthModule* GetHealthModule(); virtual class UHealthModule* GetHealthModule_Implementation() override;

};

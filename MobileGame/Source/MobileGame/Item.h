// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"


UENUM(Blueprintable)
enum class EItemTypes : uint8
{
	None = 0,
	Weapon = 1,
	Armour = 2
};

/**
 * 
 */
UCLASS(Blueprintable)
class MOBILEGAME_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int ItemID;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString ItemName;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	EItemTypes ItemType;
};

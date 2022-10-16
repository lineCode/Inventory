// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemPrototypeData.h"
#include "HBItemData.generated.h"


class UHBInventoryItemInstance;

USTRUCT(BlueprintType)
struct INVENTORY_API FPickableItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItemPrototypeData* Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count;

};

USTRUCT(BlueprintType)
struct INVENTORY_API FInventoryEntity
{
	GENERATED_BODY()
	
	FInventoryEntity(){}

	FString GetDebugString() const;
public:

	UPROPERTY()
	UHBInventoryItemInstance* Instance = 0;

	UPROPERTY()
	int32 StackCount = 0;

	UPROPERTY()
	FIntPoint Coordinates;
};
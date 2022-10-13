// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/HBInventoryItemDefinition.h"
#include "HBItemVisualFragment.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBItemVisualFragment : public UHBInventoryItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UTexture2D* ItemInventoryImage;

	UPROPERTY(EditAnywhere)
	USoundWave* ItemInventorySound;

	UPROPERTY(EditAnywhere)
	FIntPoint SlotSize;
};

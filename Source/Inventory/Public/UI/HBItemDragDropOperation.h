// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Data/HBItemData.h"
#include "HBItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	FItemData ItemData;
	
};

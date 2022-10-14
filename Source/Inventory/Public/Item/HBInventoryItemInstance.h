// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item/HBInventoryItemDefinition.h"
#include "HBInventoryItemInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class INVENTORY_API UHBInventoryItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	TSubclassOf<UHBInventoryItemDefinition> GetItemDef() const
	{
		return ItemDef;
	}

private:
	void SetItemDef(TSubclassOf<UHBInventoryItemDefinition> InDef);


	UFUNCTION(BlueprintCallable, BlueprintPure = false, meta = (DeterminesOutputType = FragmentClass))
		const UHBInventoryItemFragment* FindFragmentByClass(TSubclassOf<UHBInventoryItemFragment> FragmentClass) const;
	
	friend class UHBItemContainerComponent;

	// The item definition
	UPROPERTY()
	TSubclassOf<UHBInventoryItemDefinition> ItemDef;
	
};

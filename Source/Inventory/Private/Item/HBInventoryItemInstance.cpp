// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HBInventoryItemInstance.h"

void UHBInventoryItemInstance::SetItemDef(TSubclassOf<UHBInventoryItemDefinition> InDef)
{
	ItemDef = InDef;
}

const UHBInventoryItemFragment* UHBInventoryItemInstance::FindFragmentByClass(TSubclassOf<UHBInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UHBInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}

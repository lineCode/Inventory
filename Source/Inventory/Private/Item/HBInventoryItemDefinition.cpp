// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HBInventoryItemDefinition.h"

UHBInventoryItemDefinition::UHBInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
{
}

const UHBInventoryItemFragment* UHBInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UHBInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass!=nullptr)
	{
		for (UHBInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}

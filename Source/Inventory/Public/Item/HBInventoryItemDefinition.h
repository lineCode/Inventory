// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HBInventoryItemDefinition.generated.h"


class UHBInventoryItemInstance;

//Represents a fragment of an item definition
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UHBInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(UHBInventoryItemInstance* Instance) const {}
};

/**
 * 
 */
UCLASS(Blueprintable, Const, Abstract)
class INVENTORY_API UHBInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UHBInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
		FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display, Instanced)
		TArray<TObjectPtr<UHBInventoryItemFragment>> Fragments;

public:
	const UHBInventoryItemFragment* FindFragmentByClass(TSubclassOf<UHBInventoryItemFragment> FragmentClass) const;


	
};

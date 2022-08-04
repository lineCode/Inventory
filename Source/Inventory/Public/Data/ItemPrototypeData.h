// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemPrototypeData.generated.h"


UENUM(BlueprintType)
namespace EItemType
{
	enum Type
	{
		Default			UMETA(DisplayName = "Default"),
		Armor			UMETA(DisplayName = "Armor"),
		Sword			UMETA(DisplayName = "Sword"),
		Bow				UMETA(DisplayName = "Bow")
	};
}


/**
 * 
 */
UCLASS(BlueprintType)
class INVENTORY_API UItemPrototypeData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Size = { 1,1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType::Type> ItemType = EItemType::Default;
	
};

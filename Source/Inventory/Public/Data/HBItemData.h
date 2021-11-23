// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HBItemData.generated.h"


//UENUM()
//enum ItemType
//{
//	Default  UMETA(DisplayName = "Default"),
//	Armor    UMETA(DisplayName = "Armor"),
//	Sword    UMETA(DisplayName = "Sword"),
//	Bow		 UMETA(DisplayName = "Bow")
//};

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


USTRUCT(BlueprintType)
struct INVENTORY_API FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemDataRow();
	//FInventoryItem(int32 ID, int32 Amount);
	FItemDataRow(FName Name, int32 Amount);


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
		bool CanStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StackSize = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	ItemType ItemType = ItemType::Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType::Type> ItemType;

	bool operator==(const FItemDataRow& OtherItem) const
	{
		if (Name == OtherItem.Name)
			return true;
		return false;
	}

};

USTRUCT(BlueprintType)
struct INVENTORY_API FItemData 
{
	GENERATED_BODY()

public:
	void SetIndex(FIntPoint NewIndex);
	FIntPoint GetIndex();
	TArray<FIntPoint> GetItemCoordinates();
	TArray<FIntPoint> GetItemCoordinatesForIndex(FIntPoint NewIndex);
	FIntPoint GetSize();
	UTexture2D* GetIcon();
	FName GetName();
	int32 GetCount();
	void SetCount(int32 NewCount);
	int32 GetStackSize();
	TEnumAsByte<EItemType::Type> GetItemType();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FItemDataRow Data;


	bool operator==(const FItemData& OtherItem) const
	{
		if (Data.Name == OtherItem.Data.Name)
			return true;
		return false;
	}
};

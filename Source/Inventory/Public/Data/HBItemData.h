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
	FORCEINLINE bool IsStackable() { return Data->IsStackable; };
	TEnumAsByte<EItemType::Type> GetItemType();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItemPrototypeData* Data;


	//bool operator==(const FItemData& OtherItem) const
	//{
	//	if (Data.Name == OtherItem.Data.Name)
	//		return true;
	//	return false;
	//}
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
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/HBItemData.h"
#include "HBItemObject.generated.h"


UCLASS(BlueprintType)
class INVENTORY_API UHBItemObject : public UObject
{
	GENERATED_BODY()

public:

	UHBItemObject();

//
//	UFUNCTION(BlueprintCallable)
//		void SetItemData(FItemData NewItemData);
//
//	UFUNCTION(BlueprintCallable)
//		FIntPoint GetItemIndex();
//
//	UFUNCTION(BlueprintCallable)
//		void SetItemIndex(FIntPoint NewItemCoordinate);
//
//	UFUNCTION(BlueprintCallable)
//		TArray<FIntPoint> GetItemCoordinates();
//
//	UFUNCTION(BlueprintCallable)
//		TArray<FIntPoint> GetItemCoordinatesForIndex(FIntPoint NewIndex);
//	
//	UFUNCTION(BlueprintCallable)
//		UTexture2D* GetItemIcon();
//
//	UFUNCTION(BlueprintCallable)
//		FIntPoint GetItemSize();
//
//
//
//
//private:
//
//	FItemData ItemData;
//
//	FIntPoint Index;
//


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/HBItemData.h"
#include "HBItemVisualWidget.generated.h"


class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UHBItemVisualWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHBItemDragVisual> ClassOfItemDragVisual;

public:
	void Init(FInventoryEntity InInventorEntity);

private:
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	FInventoryEntity InventorEntity;

	
};

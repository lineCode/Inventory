// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBItemVisualWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBItemVisualWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint IconScale = {64,64}; //TODO will be dynamic

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UHBItemDragVisual> ClassOfItemDragVisual;

public:
	void SetParentSlot(class UHBItemSlotWidget* NewParentSlot); // TODO
	struct FInventoryEntity GetData();
	void SetItemIconBrush(UTexture2D* Texture);

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* ItemIcon = nullptr;

	class UHBItemSlotWidget* ParentSlot;
	
};

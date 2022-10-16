// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/HBItemData.h"
#include "HBItemSlotWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSlotDelegate, FIntPoint, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlotDragDelegate, FIntPoint, Index, FIntPoint, Size);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlotDragOnDropDelegate, FIntPoint, OldIndex, FIntPoint, NewIndex);

UCLASS(Blueprintable, BlueprintType, ClassGroup = UI)
class INVENTORY_API UHBItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* BackgroundImage = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ItemAmountText = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* MainCanvas = nullptr;

	UPROPERTY(EditAnywhere)
	UTexture2D* DefaultBG = nullptr;

	UPROPERTY(EditAnywhere)
	UTexture2D* DragBG = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHBItemVisualWidget> ItemVisualSubclass;
	
public:

	UHBItemSlotWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetItemData(FInventoryEntity NewItemObject);
	UFUNCTION(BlueprintCallable)
	void SetSlotEmpty();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;


	void SetToDragState();

	void SetToDefaultState();

	UFUNCTION(BlueprintCallable)
	void SetItemCountText(int32 StackCount); 
	
	void SetCoordinate(FIntPoint InCoordinate) { Coordinate = InCoordinate; };
	
	FIntPoint GetCoordinate() {	return Coordinate;};

	
	FSlotDelegate OnSlotClicked;
	FSlotDragDelegate OnSlotDragEnter;
	FSlotDragDelegate OnSlotDragLeave;
	FSlotDragOnDropDelegate OnSlotDragOnDrop;

private:
	FIntPoint Coordinate;
	
	UPROPERTY()
	class UHBItemVisualWidget* ChildItemVisual;
	
	FInventoryEntity InventoryEntity;
};

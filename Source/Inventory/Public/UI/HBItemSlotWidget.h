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

UCLASS(Blueprintable, BlueprintType, ClassGroup = UI)
class INVENTORY_API UHBItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UHBItemSlotWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* BackgroundImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemAmountText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* MainCanvas = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DefaultBG = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DragBG = nullptr;

	void SetToDragState();

	void SetToDefaultState();

	UFUNCTION(BlueprintCallable)
		void RefreshItemCountText(int32 StackCount); // Change as refreshh
	
	UFUNCTION(BlueprintCallable)
		void SetItemCountText(int32 Count);

	UFUNCTION(BlueprintCallable)
		void SetSlotEmpty(bool empty);

	UFUNCTION(BlueprintCallable)
		void SetItemData(FInventoryEntity NewItemObject);

	////UFUNCTION(BlueprintCallable)
	////	UHBItemData* GetItemData();

	UFUNCTION(BlueprintCallable)
	FInventoryEntity GetItemData();

	void SetIndex(int x, int y);
	FIntPoint GetIndex();

	void OnClick();

	FSlotDelegate OnSlotClicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint IconScale = { 64,64 }; //TODO will be dynamic may be ui scale

	class UHBItemContainerWidget* ParentContainer;

	FIntPoint Index;
	FInventoryEntity InventoryEntity;

	class UHBItemVisualWidget* ChildItemVisual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UHBItemVisualWidget> ItemVisualSubclass;

};

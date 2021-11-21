// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/HBItemData.h"
#include "HBItemSlotContainerWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSlotDelegate, FIntPoint, Index);

UCLASS(Blueprintable, BlueprintType, ClassGroup = UI)
class INVENTORY_API UHBItemSlotContainerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UHBItemSlotContainerWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* BackgroundImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemAmountText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* MainCanvas = nullptr;


	UFUNCTION(BlueprintCallable)
		void RefreshItemCountText(); // Change as refreshh
	
	UFUNCTION(BlueprintCallable)
		void SetItemCountText(int32 Count);

	UFUNCTION(BlueprintCallable)
		void SetItemIconBrush();

	UFUNCTION(BlueprintCallable)
		void SetSlotEmpty(bool empty);

	UFUNCTION(BlueprintCallable)
		void SetItemData(FItemData NewItemObject);

	////UFUNCTION(BlueprintCallable)
	////	UHBItemData* GetItemData();

	UFUNCTION(BlueprintCallable)
		FItemData GetItemData();

	void SetIndex(int x, int y);
	FIntPoint GetIndex();

	void OnClick();

	FSlotDelegate OnSlotClicked;



	class UHBItemContainerWidget* ParentContainer;

	FIntPoint Index;
	FItemData ItemData;
	class UHBItemSlotWidget* OwnItemSlot;
	TSubclassOf<class UHBItemSlotWidget> ItemSlotSubclass;

};

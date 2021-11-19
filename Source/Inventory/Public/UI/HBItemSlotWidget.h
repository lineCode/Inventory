// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = UI)
class UHBItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	UHBItemSlotWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemThumbnailImage = nullptr;



	UFUNCTION()
		void testFunc();


	UFUNCTION(BlueprintCallable)
		void SetItemIconBrush(UTexture2D* Texture);


	//DATA
	//UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		//FInventoryItem Item;
	//UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		//FInventoryItemData ItemData;
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		int SlotIndex;


	/*virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;



	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
		*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
		FKey DetectDragKey;

	class UHBItemSlotContainerWidget* ParentWidget;

public:

	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;



protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


};

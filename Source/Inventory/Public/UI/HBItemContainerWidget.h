// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/HBItemData.h"
#include "HBItemContainerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UHBItemContainerWidget : public UUserWidget 
{	
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUniformGridPanel* SlotGrid = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHBItemSlotWidget> ItemSlotBGSubclass;

public:

	virtual void NativeConstruct() override;
	
	UHBItemContainerWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void InitContainer(class UHBItemContainerComponent* InItemContainerComponent);

	UFUNCTION(BlueprintCallable)
	void RefreshContainerWidget();

	UFUNCTION(BlueprintCallable)
	void OnItemDeleted(FIntPoint Coordinate);

	UFUNCTION(BlueprintCallable)
	void OnItemAdded(FIntPoint Coordinate, FInventoryEntity InventortyEntry);

	UFUNCTION(BlueprintCallable)
	void OnCountChanged(FIntPoint Coordinate, int32 StackCount);

	UFUNCTION(BlueprintCallable)
	void OnSlotClicked(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
	void OnSlotDragEnter(FIntPoint Index, FIntPoint Size);

	UFUNCTION(BlueprintCallable)
	void OnSlotDragLeave(FIntPoint Index, FIntPoint Size);

	UFUNCTION(BlueprintCallable)
	void OnSlotDragOnDrop(FIntPoint OldCoordinate, FIntPoint NewCoordinate);

	class UHBItemSlotWidget* GetItemSlotAtCoordinate(FIntPoint Coordinate);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateOffset(FIntPoint Coordinate, FIntPoint Offset);


	void MarkSlots(FIntPoint Coordinate, FIntPoint Size);
	void ClearMarkedSlots();


private:
	class UHBItemContainerComponent* ItemContainerComponent;
	TArray<UHBItemSlotWidget*> DirtMarkedSlots;	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	UPROPERTY(EditAnywhere)
	USoundBase* Sound;

public:

	virtual void NativeConstruct() override;
	
	UHBItemContainerWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void InitContainer(class UHBItemContainerComponent* InItemContainerComponent);


	UFUNCTION(BlueprintCallable)
		void RefreshContainerWidget();

	UFUNCTION(BlueprintCallable)
		void OnItemDeleted(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
		void OnItemAdded(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
		void OnCountChanged(FIntPoint Index, int32 StackCount);

	UFUNCTION(BlueprintCallable)
		void OnSlotClicked(FIntPoint Index);

	class UHBItemSlotWidget* GetItemSlotAtCoordinate(FIntPoint Coordinate);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateOffset(FIntPoint Coordinate, FIntPoint Offset);
	//class UHBItemSlotWidget* GetItemSlotAtCoordinateRight(FIntPoint Coordinate, int32 Amount);
	//class UHBItemSlotWidget* GetItemSlotAtCoordinateLeft(FIntPoint Coordinate, int32 Amount);
	//class UHBItemSlotWidget* GetItemSlotAtCoordinateUp(FIntPoint Coordinate, int32 Amount);
	//class UHBItemSlotWidget* GetItemSlotAtCoordinateDown(FIntPoint Coordinate, int32 Amount);
	//

	void MarkSlots(FIntPoint Coordinate, FIntPoint Size);
	void ClearMarkedSlots();
	TArray<UHBItemSlotWidget*> DirtMarkedSlots;

	TArray<TArray<class UHBItemSlotWidget*>>ItemSlots;


	UFUNCTION(BlueprintCallable)
		UHBItemContainerComponent* GetItemContainerComponent();

	class UHBItemContainerComponent* ItemContainerComponent;

};

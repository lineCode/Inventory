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
public:

	virtual void NativeConstruct() override;
	UHBItemContainerWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UUniformGridPanel* SlotGrid = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UHBItemSlotWidget> ItemSlotBGSubclass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound;


	UFUNCTION(BlueprintCallable)
		void InitContainer(class UHBItemContainerComponent* _ItemContainerComponent);

	UFUNCTION(BlueprintCallable)
		void RefreshContainerWidget();

	UFUNCTION(BlueprintCallable)
		void OnItemDeleted(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
		void OnItemAdded(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
		void OnCountChanged(FIntPoint Index);

	UFUNCTION(BlueprintCallable)
		void OnSlotClicked(FIntPoint Index);

	class UHBItemSlotWidget* GetItemSlotAtCoordinate(FIntPoint Coordinate);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateRight(FIntPoint Coordinate, int32 Amount);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateLeft(FIntPoint Coordinate, int32 Amount);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateUp(FIntPoint Coordinate, int32 Amount);
	class UHBItemSlotWidget* GetItemSlotAtCoordinateDown(FIntPoint Coordinate, int32 Amount);
	

	void MarkSlots(FIntPoint Coordinate, FIntPoint Size);
	void ClearMarkedSlots();
	TArray<UHBItemSlotWidget*> DirtMarkedSlots;

	TArray<TArray<class UHBItemSlotWidget*>>ItemSlots;


	UFUNCTION(BlueprintCallable)
		UHBItemContainerComponent* GetItemContainerComponent();

	class UHBItemContainerComponent* ItemContainerComponent;

};

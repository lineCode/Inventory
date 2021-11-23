// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/HBItemData.h"
#include "HBItemContainerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryBasicDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSlotChangedDelegate, FIntPoint, Index);



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UHBItemContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHBItemContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Utils")
		void SetContainerSize(FIntPoint NewSize);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
	//	bool AddRandomItem(UHBItemData* ItemData);

	//HELPER FUNCTIONS

	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool IncreaseItemCountAtSlot(FIntPoint Index, int32 CountToAdd);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItem(FName ItemName, int32 Count);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItemAsStackable(FItemData* Item);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItemAsNonStackable(FItemData* Item);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
		void AddItemDirectly(FItemData* ItemData, FIntPoint Index);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
	//	void AddItemDirectly(FItemData ItemData, FIntPoint Index);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		void DeleteItemAtIndex(FIntPoint Index);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		void MoveItem(FIntPoint OldIndex, FIntPoint NewIndex);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItemAvailableSlot(FItemData* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		FIntPoint FindAvailableSlot(FItemData Item, bool& found);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool IsItemSuitableForNewIndex(FItemData Item, FIntPoint NewCoordinates);

	TArray<TTuple<FIntPoint, int32>> FindFreeStackableSlots(FName Name);

	//UFUNCTION(BlueprintCallable, Category = "Utils")
	FItemData* FindItemAtIndex(FIntPoint Index);

	//UFUNCTION()
	TArray<TArray<bool>> GetAvailableSlots();

	//UFUNCTION(BlueprintCallable, Category = "Utils")
	//	bool IsSlotEmptyAtIndex(int x, int y);

	TArray<FItemData*> GetItems();

	UFUNCTION(BlueprintCallable, Category = "Utils")
		FIntPoint GetContainerSize();

	UPROPERTY(BlueprintAssignable)
		FInventoryBasicDelegate InventoryHasChanged;

	UPROPERTY(BlueprintAssignable)
		FItemSlotChangedDelegate OnItemDeleted;

	UPROPERTY(BlueprintAssignable)
		FItemSlotChangedDelegate OnItemAdded;

	UPROPERTY(BlueprintAssignable)
		FItemSlotChangedDelegate OnItemCountChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* ItemDatabase;

	TArray<FItemData*> Items;

	FItemData GetItemDataByNameDatabase(FName Name);

	FIntPoint ContainerSize;

	TArray<TArray<bool>> AvailableSlots;
	bool AvailableSlotsIsDirty = true;

};

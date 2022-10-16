// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/HBItemData.h"
#include "HBItemContainerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryBasicDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSlotChangedDelegate, FIntPoint, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemSlotCountChangedDelegate, FIntPoint, Index,int32, StackCount);

class UHBInventoryItemDefinition;
class UHBInventoryItemInstance;

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

	//UFUNCTION(BlueprintCallable, Category = "Utils")
	bool IncreaseEntryStackCount(FInventoryEntity* Entry, int32 CountToAdd);



	void DeleteItemAtIndex(FIntPoint Index);

	void MoveItem(FIntPoint OldIndex, FIntPoint NewIndex);


	UFUNCTION(BlueprintCallable, Category = "Utils")
	FIntPoint GetAvailableSlot(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, bool& found);

	TArray<FIntPoint> GetItemCoordinatesForIndex(FIntPoint NewIndex, FIntPoint Size);

	UFUNCTION(BlueprintCallable, Category = "Utils")
	bool IsCoordinatesAvailable(TArray<FIntPoint> ItemCoordinates);

	FInventoryEntity FindItemEntryAtIndex(FIntPoint Index);
	int FindEntryIndexAtCoordinates(FIntPoint Coordinate);

	UFUNCTION(BlueprintCallable, Category = "Utils")
	FIntPoint GetContainerSize();

	UPROPERTY(BlueprintAssignable)
	FInventoryBasicDelegate InventoryHasChanged;

	UPROPERTY(BlueprintAssignable)
	FItemSlotChangedDelegate OnItemDeleted;

	UPROPERTY(BlueprintAssignable)
	FItemSlotChangedDelegate OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FItemSlotCountChangedDelegate OnItemCountChanged;


	UPROPERTY()
	FIntPoint ContainerSize;

	TArray<bool> AvailableSlots;

	int GetAvailableSlotIndex(FIntPoint Coordinate);

	bool AvailableSlotsIsDirty = true;

	// Lyra

	UPROPERTY()
	TArray<FInventoryEntity> Entries;

	UHBInventoryItemInstance* AddEntiry(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition,int32 StackCount, FIntPoint Coordinates);
	
	void AddItemDef(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount);

	//UHBInventoryItemInstance* AddEntiryAsStackable(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount);
	
	void AddItemDefAsNonStackable(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount);

	

	TArray<TTuple<FIntPoint, int32>> GetUnfilledStackableSlots(TSubclassOf<UHBInventoryItemDefinition> ItemDef);
	
	//UFUNCTION(BlueprintCallable, Category = "Utils")
	TTuple<FIntPoint, int32> GetAvailableSlotCoordinate(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, bool& bFound, bool& bIsStack);

	void MarkSlotsAvilable(TArray<FIntPoint> SlotCoordinates);
	void MarkSlotsNonAvilable(TArray<FIntPoint> SlotCoordinates);


	UFUNCTION(BlueprintCallable)
	USoundWave* GetEntrySound(int32 Index);
};
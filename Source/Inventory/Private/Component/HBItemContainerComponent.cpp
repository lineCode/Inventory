#include "Component/HBItemContainerComponent.h"

// Sets default values for this component's properties
UHBItemContainerComponent::UHBItemContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHBItemContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetContainerSize(ContainerSize);

}

// Called every frame
void UHBItemContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHBItemContainerComponent::SetContainerSize(FIntPoint NewSize)
{
	ContainerSize = NewSize;


	TArray<bool> Row;
	for (size_t x = 0; x < NewSize.X; x++)
	{
		Row.Add(false);
	}

	for (size_t i = 0; i < NewSize.Y; i++)
	{
		AvailableSlots.Add(Row);
	}

	//ContainerSize = NewSize;

	//for (size_t i = 0; i < ContainerSize.X; i++)
	//{
	//	TArray<bool> SlotRow;
	//	for (size_t j = 0; j < ContainerSize.Y; j++)
	//	{
	//		SlotRow.Add(false);
	//	}
	//	Slots.Add(SlotRow);
	//}
}


bool UHBItemContainerComponent::AddItem(FItemData Item)
{
	if (Item.Data.CanStackable)
	{
		return AddItemAsStackable(Item);
	}
	else
	{
		return AddItemAsNonStackable(Item);
	}
}

bool UHBItemContainerComponent::AddItemAsStackable(FItemData Item)
{
	TArray<TTuple<FIntPoint, int32>> FreeStackableSlots = FindFreeStackableSlots(Item.GetName());

	int32 RemainItemCount = Item.GetCount();

	for (TTuple<FIntPoint, int32> SlotTuple : FreeStackableSlots)
	{
		int32 ItemCountForTheSlot = RemainItemCount - SlotTuple.Value;
		if (ItemCountForTheSlot<=0)
		{
			//Icrease  SSlotTuple.Key indexed Count(RemainItemCount)
			RemainItemCount -= RemainItemCount;
			break;
		}
		else
		{
			//Icrease SlotTuple.Key indexed count(SlotTuple.Value)
			RemainItemCount -= SlotTuple.Value;
		}
	}

	if (RemainItemCount>0)
	{
		Item.Count = RemainItemCount;
		AddItemAsNonStackable(Item);
	}

}

bool UHBItemContainerComponent::AddItemAsNonStackable(FItemData Item)
{

	return false;
}

void UHBItemContainerComponent::AddItemDirectly(FItemData ItemData, FIntPoint Index)
{
	UE_LOG(LogExec, Warning, TEXT("UHBItemContainerComponent::AddItemDirectly Index %s"), *Index.ToString());
	ItemData.SetIndex(Index);
	UE_LOG(LogExec, Warning, TEXT("UHBItemContainerComponent::AddItemDirectly 2"));

	Items.Add(ItemData);
	OnItemAdded.Broadcast(Index);
	//InventoryHasChanged.Broadcast(); //call delegate container updated
	AvailableSlotsIsDirty = true;
}

void UHBItemContainerComponent::DeleteItemAtIndex(FIntPoint Index)
{
	//UHBItemObject* Item = FindItemAtIndex(Index);
	FItemData ItemData;//TODO
	Items.Remove(ItemData);
	OnItemDeleted.Broadcast(Index);
	//InventoryHasChanged.Broadcast(); //call delegate container updated
	AvailableSlotsIsDirty = true;

}

void UHBItemContainerComponent::MoveItem(FIntPoint OldIndex, FIntPoint NewIndex)
{
	FItemData* Item = FindItemAtIndex(OldIndex);

	if (IsItemSuitableForNewIndex(*Item, NewIndex))
	{
		OnItemDeleted.Broadcast(OldIndex);
		Item->SetIndex(NewIndex);
		OnItemAdded.Broadcast(NewIndex);
		AvailableSlotsIsDirty = true;
	}
}

bool UHBItemContainerComponent::AddItemAvailableSlot(FName ItemName, int32 Count)
{
	bool bFound;

	FItemDataRow* ItemDataRow = ItemDatabase->FindRow<FItemDataRow>(ItemName, "");

	if (!ItemDataRow)
	{
		return false;
	}

	FItemData ItemData;
	ItemData.Data = *ItemDataRow;
	ItemData.Count = Count;

	FIntPoint FoundIndex = FindAvailableSlot(ItemData, bFound);
	ItemData.SetIndex(FoundIndex);


	//UHBItemObject* NewItem = NewObject<UHBItemObject>(this, UHBItemObject::StaticClass());
	//DuplicateObject(ItemData, NewItem);
	//NewItem->SetItemIndex(FoundIndex);

	if (bFound)
	{
		AddItemDirectly(ItemData, FoundIndex);
		//InventoryHasChanged.Broadcast(); //call delegate container updated
		AvailableSlotsIsDirty = true;
	}
	return true;
}

FIntPoint UHBItemContainerComponent::FindAvailableSlot(FItemData Item, bool& found)
{
	found = false;

	for (size_t x = 0; x < ContainerSize.X; x++)
	{
		for (size_t y = 0; y < ContainerSize.Y; y++)
		{
			if (IsItemSuitableForNewIndex(Item, FIntPoint(x, y)))
			{
				found = true;
				return FIntPoint(x, y);
			}

		}
	}
	return FIntPoint();
}

bool UHBItemContainerComponent::IsItemSuitableForNewIndex(FItemData Item, FIntPoint NewCoordinates)
{
	TArray<FIntPoint> ItemNewCoordinates = Item.GetItemCoordinatesForIndex(NewCoordinates);
	TArray<TArray<bool>> SlotStatus = GetAvailableSlots();

	for (FIntPoint Coordinate : ItemNewCoordinates)
	{
		if (!SlotStatus.IsValidIndex(Coordinate.X))
		{
			return false;
		}
		if (!SlotStatus[Coordinate.X].IsValidIndex(Coordinate.Y))
		{
			return false;
		}
		if (SlotStatus[Coordinate.X][Coordinate.Y])
		{
			return false;
		}
	}

	return true;
}

TArray<TTuple<FIntPoint,int32>> UHBItemContainerComponent::FindFreeStackableSlots(FName Name)
{
	TArray<TTuple<FIntPoint, int32>> FreeSlots;

	for (FItemData Item : Items)
	{
		if (Item.GetName() == Name)
		{
			int FreeStackCount = Item.GetStackSize() - Item.GetCount();
			
			if (FreeStackCount > 0)
			{
				FreeSlots.Add(TTuple<FIntPoint, int32>(Item.GetIndex(),FreeStackCount));
			}

		}
	}
	return FreeSlots;
}


FItemData* UHBItemContainerComponent::FindItemAtIndex(FIntPoint Index)
{

	for (size_t i = 0; i < Items.Num(); i++)
	{
		if (Items[i].GetIndex() == Index)
		{
			return &Items[i];
		}
	}
	return nullptr;
}

TArray<TArray<bool>> UHBItemContainerComponent::GetAvailableSlots()
{
	if (!AvailableSlotsIsDirty)
	{
		return AvailableSlots;
	}

	AvailableSlots.Empty();

	TArray<bool> Row;

	for (size_t Y = 0; Y < ContainerSize.Y; Y++)
	{
		Row.Add(false);
	}

	for (size_t X = 0; X < ContainerSize.X; X++)
	{
		AvailableSlots.Add(Row);
	}

	TArray<FItemData> ItemInContainer = GetItems();

	for (size_t i = 0; i < ItemInContainer.Num(); i++)
	{
		FItemData ItemObj = ItemInContainer[i];

		
		TArray<FIntPoint> ItemCoordinates = ItemObj.GetItemCoordinates();

		for (FIntPoint Coordinate : ItemCoordinates)
		{
			AvailableSlots[Coordinate.X][Coordinate.Y] = true;
		}
		

	}
	AvailableSlotsIsDirty = false;

	return AvailableSlots;
}

TArray<FItemData> UHBItemContainerComponent::GetItems()
{
	return Items;
}

FIntPoint UHBItemContainerComponent::GetContainerSize()
{
	return ContainerSize;
}

FItemData UHBItemContainerComponent::GetItemDataByNameDatabase(FName Name)
{
	UE_LOG(LogExec, Warning, TEXT(" UHBItemContainerComponent::GetItemDataByNameDatabase"));
	FItemData EquipmentItemData;
	return EquipmentItemData;
}



//bool UHBItemContainerComponent::IsSlotEmpty(int32 index)
//{
//	bool IsEmpty = false;
//
//
//
//
//	return IsEmpty;
//}
#include "Component/HBItemContainerComponent.h"
#include "Item/HBInventoryItemInstance.h"
#include "Item/HBInventoryItemDefinition.h"
#include "Item/Fragments/HBItemVisualFragment.h"

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


bool UHBItemContainerComponent::IncreaseItemCountAtSlot(FIntPoint Index, int32 CountToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("IncreaseItemCountAtSlot "));

	FItemData* Item = FindItemAtIndex(Index);

	int32 OldCount = Item->GetCount();
	Item->SetCount(OldCount + CountToAdd);

	OnItemCountChanged.Broadcast(Index);

	return false;
}

bool UHBItemContainerComponent::AddItem(FItemData ItemData, int32 Count)
{
	if (ItemData.IsStackable())
	{
		return AddItemAsStackable(ItemData);
	}
	else
	{
		return AddItemAsNonStackable(ItemData);
	}
}

bool UHBItemContainerComponent::AddItemAsStackable(FItemData ItemData)
{
	TArray<TTuple<FIntPoint, int32>> FreeStackableSlots = FindFreeStackableSlots(ItemData.GetName());

	int32 RemainItemCount = ItemData.GetCount();

	for (TTuple<FIntPoint, int32> SlotTuple : FreeStackableSlots)
	{
		int32 ItemCountForTheSlot = RemainItemCount - SlotTuple.Value;
		if (ItemCountForTheSlot<=0)
		{
			//Icrease  SSlotTuple.Key indexed Count(RemainItemCount)
			IncreaseItemCountAtSlot(SlotTuple.Key, RemainItemCount);
			RemainItemCount -= RemainItemCount;
			break;
		}
		else
		{
			//Icrease SlotTuple.Key indexed count(SlotTuple.Value)
			IncreaseItemCountAtSlot(SlotTuple.Key, SlotTuple.Value);
			RemainItemCount -= SlotTuple.Value;
		}
	}

	if (RemainItemCount>0)
	{
		ItemData.Count = RemainItemCount;
		AddItemAsNonStackable(ItemData);
	}
	return true;
}

bool UHBItemContainerComponent::AddItemAsNonStackable(FItemData ItemData)
{
	AddItemToAvailableSlot(ItemData);
	return false;
}

void UHBItemContainerComponent::AddItemDirectly(FItemData ItemData, FIntPoint Index)
{
	ItemData.SetIndex(Index);
	Items.Add(ItemData);
	OnItemAdded.Broadcast(Index);
	AvailableSlotsIsDirty = true;
}

void UHBItemContainerComponent::DeleteItemAtIndex(FIntPoint Index)
{
	//UHBItemObject* Item = FindItemAtIndex(Index);
	//FItemData* ItemData;//TODO
	//Items.Remove(ItemData);
	//OnItemDeleted.Broadcast(Index);
	////InventoryHasChanged.Broadcast(); //call delegate container updated
	//AvailableSlotsIsDirty = true;

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

bool UHBItemContainerComponent::AddItemToAvailableSlot(FItemData ItemData)
{
	bool bFound;

	FIntPoint FoundIndex = FindAvailableSlot(ItemData, bFound);

	if (bFound)
	{
		AddItemDirectly(ItemData, FoundIndex);
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

	TArray<FItemData*> ItemInContainer = GetItems();

	for (size_t i = 0; i < ItemInContainer.Num(); i++)
	{
		FItemData* Item = ItemInContainer[i];

		
		TArray<FIntPoint> ItemCoordinates = Item->GetItemCoordinates();

		for (FIntPoint Coordinate : ItemCoordinates)
		{
			AvailableSlots[Coordinate.X][Coordinate.Y] = true;
		}
		

	}
	AvailableSlotsIsDirty = false;

	return AvailableSlots;
}

TArray<FItemData*> UHBItemContainerComponent::GetItems()
{
	TArray<FItemData*> ItemDataRef;

	for (size_t i = 0; i < Items.Num(); i++)
	{
		ItemDataRef.Add(&Items[i]);
	}
	return ItemDataRef;
}

FIntPoint UHBItemContainerComponent::GetContainerSize()
{
	return ContainerSize;
}

UHBInventoryItemInstance* UHBItemContainerComponent::AddEntiry(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount)
{
	UHBInventoryItemInstance* Result = nullptr;

	FInventoryEntity& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UHBInventoryItemInstance>(this);
	NewEntry.Instance->SetItemDef(ItemDefinition);

	for (UHBInventoryItemFragment* Fragment : GetDefault<UHBInventoryItemDefinition>(ItemDefinition)->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(NewEntry.Instance);
		}
	}

	NewEntry.StackCount = StackCount;

	Result = NewEntry.Instance;

	return Result;
}

USoundWave* UHBItemContainerComponent::GetEntrySound(int32 Index)
{
	if (Entries.IsValidIndex(Index))
	{
		if (Entries[Index].Instance)
		{
			const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(Entries[Index].Instance->FindFragmentByClass(UHBItemVisualFragment::StaticClass()));
			if (ItemVisualFragment)
			{
				return ItemVisualFragment->ItemInventorySound;
			}
		}
		
	}
	return nullptr;
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
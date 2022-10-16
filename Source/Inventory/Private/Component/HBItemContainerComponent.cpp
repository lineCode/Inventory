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



bool UHBItemContainerComponent::IncreaseEntryStackCount(FInventoryEntity* Entry, int32 CountToAdd)
{
	Entry->StackCount += CountToAdd;
	OnItemCountChanged.Broadcast(Entry->Coordinates, Entry->StackCount);

	return true;
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
	int Index = FindEntryIndexAtCoordinates(OldIndex);

	FInventoryEntity* Item = &Entries[Index];
	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(Entries[Index].Instance->GetItemDef(), UHBItemVisualFragment::StaticClass()));

	if (IsCoordinatesAvailable(GetItemCoordinatesForIndex(NewIndex, ItemVisualFragment->SlotSize)))
	{
		OnItemDeleted.Broadcast(OldIndex);
		Item->Coordinates = NewIndex;
		
		TArray<FIntPoint> OldItemItemCoordinate = GetItemCoordinatesForIndex(OldIndex, ItemVisualFragment->SlotSize);
		TArray<FIntPoint> NewItemItemCoordinate = GetItemCoordinatesForIndex(NewIndex, ItemVisualFragment->SlotSize);

		MarkSlotsAvilable(OldItemItemCoordinate);
		MarkSlotsNonAvilable(NewItemItemCoordinate);

		OnItemAdded.Broadcast(NewIndex,*Item);
	}

}

FIntPoint UHBItemContainerComponent::GetAvailableSlot(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, bool& found)
{

	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(ItemDefinition, UHBItemVisualFragment::StaticClass()));
	FIntPoint ItemSize = ItemVisualFragment->SlotSize;

	found = false;

	for (size_t x = 0; x < ContainerSize.X; x++)
	{
		for (size_t y = 0; y < ContainerSize.Y; y++)
		{
			TArray<FIntPoint> ItemCoordinate = GetItemCoordinatesForIndex(FIntPoint(x, y), ItemSize);
			
			if (IsCoordinatesAvailable(ItemCoordinate))
			{
				found = true;
				return FIntPoint(x, y);
			}

		}
	}
	return FIntPoint();
}

TArray<FIntPoint> UHBItemContainerComponent::GetItemCoordinatesForIndex(FIntPoint NewIndex, FIntPoint Size)
{
	TArray<FIntPoint> Coordinates;

	int X = Size.X;
	int Y = Size.Y;

	for (size_t x = 0; x < X; x++)
	{
		for (size_t y = 0; y < Y; y++)
		{
			Coordinates.Add(NewIndex + FIntPoint(x, y));
		}
	}
	return Coordinates;
}



int UHBItemContainerComponent::FindEntryIndexAtCoordinates(FIntPoint Coordinate)
{
	for (size_t i = 0; i < Entries.Num(); i++)
	{
		if (Entries[i].Coordinates == Coordinate)
		{
			return i;
		}
	}
	return -1;
}

FInventoryEntity UHBItemContainerComponent::FindItemEntryAtIndex(FIntPoint Index)
{

	for (size_t i = 0; i < Entries.Num(); i++)
	{
		if (Entries[i].Coordinates == Index)
		{
			return Entries[i];
		}
	}
	return FInventoryEntity();
}

UHBInventoryItemInstance* UHBItemContainerComponent::AddEntiry(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount, FIntPoint Coordinates)
{
	UHBInventoryItemInstance* Result = nullptr;

	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(ItemDefinition, UHBItemVisualFragment::StaticClass()));

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
	NewEntry.Coordinates = Coordinates;

	Result = NewEntry.Instance;

	//AvailableSlotsIsDirty = true;
	TArray<FIntPoint> ItemCoordinate = GetItemCoordinatesForIndex(NewEntry.Coordinates, ItemVisualFragment->SlotSize);

	MarkSlotsNonAvilable(ItemCoordinate);

	OnItemAdded.Broadcast(Coordinates, NewEntry);

	return Result;
}

void UHBItemContainerComponent::AddItemDef(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount)
{
	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(ItemDefinition, UHBItemVisualFragment::StaticClass()));
	
	int RemainStackCount = StackCount;
	int OldRemainStackCount = StackCount;

	if (ItemVisualFragment->Stackable)
	{
		bool bFound = false;
		bool bIsStack = false;

		do
		{
			TTuple<FIntPoint, int32> AvailableSlot = GetAvailableSlotCoordinate(ItemDefinition, bFound, bIsStack);

			OldRemainStackCount = RemainStackCount;
			RemainStackCount = FMath::Clamp(RemainStackCount - AvailableSlot.Value, 0, 999);
			int ItemCountToAdd = OldRemainStackCount - RemainStackCount;

			if (bFound)
			{
				if (bIsStack)
				{
					//AddOnCordinate
					int EntryIndex = FindEntryIndexAtCoordinates(AvailableSlot.Key);
					IncreaseEntryStackCount(&Entries[EntryIndex], ItemCountToAdd);
				}
				else
				{

					AddEntiry(ItemDefinition, ItemCountToAdd, AvailableSlot.Key);
				}
			}

			if (RemainStackCount <= 0) break;

		} while (bFound);

	}
	else
	{
		AddItemDefAsNonStackable(ItemDefinition, StackCount);
	}
}

void UHBItemContainerComponent::AddItemDefAsNonStackable(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, int32 StackCount)
{
	bool bFound;

	FIntPoint FoundIndex = GetAvailableSlot(ItemDefinition, bFound);

	if (bFound)
	{
		AddEntiry(ItemDefinition, StackCount, FoundIndex);
	}
}

TArray<TTuple<FIntPoint, int32>> UHBItemContainerComponent::GetUnfilledStackableSlots(TSubclassOf<UHBInventoryItemDefinition> ItemDef)
{
	TArray<TTuple<FIntPoint, int32>> FreeSlots;

	for (FInventoryEntity Entry : Entries)
	{
		if (Entry.Instance->GetItemDef() == ItemDef)
		{
			const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(Entry.Instance->FindFragmentByClass(UHBItemVisualFragment::StaticClass()));
			int FreeStackCount = ItemVisualFragment->MaxStack - Entry.StackCount;

			if (FreeStackCount > 0)
			{
				FreeSlots.Add(TTuple<FIntPoint, int32>(Entry.Coordinates, FreeStackCount));
			}

		}
	}
	return FreeSlots;
}


TTuple<FIntPoint, int32> UHBItemContainerComponent::GetAvailableSlotCoordinate(TSubclassOf<UHBInventoryItemDefinition>ItemDefinition, bool& bFound,bool& bIsStack)
{
	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(ItemDefinition, UHBItemVisualFragment::StaticClass()));
	FIntPoint ItemSize = ItemVisualFragment->SlotSize;

	bFound = false;
	

	for (FInventoryEntity Entry : Entries)
	{
		if (Entry.Instance->GetItemDef() == ItemDefinition)
		{
			int FreeStackCount = ItemVisualFragment->MaxStack - Entry.StackCount;

			if (FreeStackCount > 0)
			{
				bIsStack = true;
				bFound = true;
				return TTuple<FIntPoint, int32>(Entry.Coordinates, FreeStackCount);
			}
		}
	}


	for (size_t x = 0; x < ContainerSize.X; x++)
	{
		for (size_t y = 0; y < ContainerSize.Y; y++)
		{
			TArray<FIntPoint> ItemCoordinate = GetItemCoordinatesForIndex(FIntPoint(x, y), ItemSize);

			if (IsCoordinatesAvailable(ItemCoordinate))
			{
				bIsStack = false;
				bFound = true;
				return TTuple<FIntPoint, int32>(FIntPoint(x, y), ItemVisualFragment->MaxStack);
			}

		}
	}
	return TTuple<FIntPoint, int32>();
}

void UHBItemContainerComponent::MarkSlotsAvilable(TArray<FIntPoint> SlotCoordinates)
{
	for (FIntPoint SlotCoordinate : SlotCoordinates)
	{
		AvailableSlots[GetAvailableSlotIndex(SlotCoordinate)] = true;
	}

}

void UHBItemContainerComponent::MarkSlotsNonAvilable(TArray<FIntPoint> SlotCoordinates)
{
	for (FIntPoint SlotCoordinate : SlotCoordinates)
	{
		AvailableSlots[GetAvailableSlotIndex(SlotCoordinate)] = false;
	}

}

int UHBItemContainerComponent::GetAvailableSlotIndex(FIntPoint Coordinate)
{
	return ContainerSize.Y * Coordinate.X + Coordinate.Y;
}

bool UHBItemContainerComponent::IsCoordinatesAvailable(TArray<FIntPoint> ItemCoordinates)
{
	TArray<bool> SlotStatus = AvailableSlots;// = GetAvailableSlots();

	for (FIntPoint Coordinate : ItemCoordinates)
	{
		if (!AvailableSlots.IsValidIndex(GetAvailableSlotIndex(Coordinate)))
		{
			return false;
		}
		if (!AvailableSlots[GetAvailableSlotIndex(Coordinate)])
		{
			return false;
		}
	}

	return true;
}

void UHBItemContainerComponent::SetContainerSize(FIntPoint NewSize)
{
	ContainerSize = NewSize;
	AvailableSlots.Init(true, ContainerSize.X * ContainerSize.Y);
}
FIntPoint UHBItemContainerComponent::GetContainerSize()
{
	return ContainerSize;
}

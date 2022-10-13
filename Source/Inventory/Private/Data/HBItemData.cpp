

#include "Data/HBItemData.h"

void FItemData::SetIndex(FIntPoint NewIndex)
{
	Index = NewIndex;
}

FIntPoint FItemData::GetIndex()
{
	return Index;
}

TArray<FIntPoint> FItemData::GetItemCoordinates()
{
	UE_LOG(LogTemp, Warning, TEXT("GetItemCoordinates()"));
	TArray<FIntPoint> Coordinates;

	int X = Data->Size.X;
	int Y = Data->Size.Y;

	for (size_t x = 0; x < X; x++)
	{
		for (size_t y = 0; y < Y; y++)
		{
			Coordinates.Add(Index + FIntPoint(x, y));
		}
	}

	return Coordinates;

}

TArray<FIntPoint> FItemData::GetItemCoordinatesForIndex(FIntPoint NewIndex)
{
	TArray<FIntPoint> Coordinates;

	int X = Data->Size.X;
	int Y = Data->Size.Y;

	for (size_t x = 0; x < X; x++)
	{
		for (size_t y = 0; y < Y; y++)
		{
			Coordinates.Add(NewIndex + FIntPoint(x, y));
		}
	}
	return Coordinates;
}

FIntPoint FItemData::GetSize()
{
	return Data->Size;
}

UTexture2D* FItemData::GetIcon()
{
	return Data->Icon;
}

FName FItemData::GetName()
{
	return Data->Name;
}

int32 FItemData::GetCount()
{
	return Count;
}

void FItemData::SetCount(int32 NewCount)
{
	Count = NewCount;
}

int32 FItemData::GetStackSize()
{
	return Data->StackSize;
}

TEnumAsByte<EItemType::Type> FItemData::GetItemType()
{
	return Data->ItemType;
}


/////INVENTORY ENTITY



FString FInventoryEntity::GetDebugString() const
{
	unimplemented();
	return FString();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HBItemObject.h"

UHBItemObject::UHBItemObject()
{
}

//void UHBItemObject::SetItemData(FItemData NewItemData)
//{
//	ItemData = NewItemData;
//	//ItemIndex = NewItemData->ItemCoordinate;
//
//	//ItemName = NewItemData->ItemName;
//	//ItemIcon = NewItemData->ItemIcon;
//	//ItemSize = NewItemData->ItemSize;
//}
//
//FIntPoint UHBItemObject::GetItemIndex()
//{
//	return Index;
//}
//
//void UHBItemObject::SetItemIndex(FIntPoint NewItemIndex)
//{
//	Index = NewItemIndex;
//}
//
//TArray<FIntPoint> UHBItemObject::GetItemCoordinates()
//{
//	UE_LOG(LogTemp, Warning, TEXT("GetItemCoordinates()"));
//	TArray<FIntPoint> Coordinates;
//
//	int X = ItemData.Size.X;
//	int Y = ItemData.Size.Y;
//
//	for (size_t x = 0; x < X; x++)
//	{
//		for (size_t y = 0; y < Y; y++)
//		{
//			Coordinates.Add(GetItemIndex() + FIntPoint(x, y));
//		}
//	}
//
//	return Coordinates;
//
//}
//
//TArray<FIntPoint> UHBItemObject::GetItemCoordinatesForIndex(FIntPoint NewIndex)
//{
//	TArray<FIntPoint> Coordinates;
//
//	int X = ItemData.Size.X;
//	int Y = ItemData.Size.Y;
//
//	for (size_t x = 0; x < X; x++)
//	{
//		for (size_t y = 0; y < Y; y++)
//		{
//			Coordinates.Add(NewIndex + FIntPoint(x, y));
//		}
//	}
//	return Coordinates;
//}
//
//UTexture2D* UHBItemObject::GetItemIcon()
//{
//	return ItemData.Icon;
//}
//
//FIntPoint UHBItemObject::GetItemSize()
//{
//	return ItemData.Size;
//}

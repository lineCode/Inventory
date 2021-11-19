// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DragDrop/HBItemDragVisual.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

void UHBItemDragVisual::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHBItemDragVisual::SetSize(FVector2D Size)
{
	UCanvasPanelSlot* ItemImageSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);

	if (ItemImageSlot)
	{
		ItemImageSlot->SetSize(Size);
	}
}

void UHBItemDragVisual::SetImage(UTexture2D* ItemImageTexture)
{
	if (ItemImageTexture)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemImageTexture);
		ItemImage->SetBrush(Brush);
	}
}

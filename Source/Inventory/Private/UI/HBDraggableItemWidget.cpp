// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBDraggableItemWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"


void UHBDraggableItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemThumbnailImage && ItemIcon)
	{

		//ItemThumbnailImage->SetBrushFromTexture(ItemData.Thumbnail, true);
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemIcon);

		//Brush.set
		ItemThumbnailImage->SetBrush(Brush);
	}

}

void UHBDraggableItemWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(ItemThumbnailImage);
	if (slot)
	{
		slot->SetSize(FVector2D(640, 640));
		UE_LOG(LogTemp, Warning, TEXT("UHBDraggableItemWidget"));
	}

}

UHBDraggableItemWidget::UHBDraggableItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}


void UHBDraggableItemWidget::SetSize(FVector2D Size)
{
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(ItemThumbnailImage->Slot);

	if (slot)
	{
		slot->SetSize(Size);
	}
	
}
void UHBDraggableItemWidget::SetImage(UTexture2D* Image)
{

	if (ItemThumbnailImage && Image)
	{

		//ItemThumbnailImage->SetBrushFromTexture(ItemData.Thumbnail, true);
		FSlateBrush Brush;
		Brush.SetResourceObject(Image);

		//Brush.set
		ItemThumbnailImage->SetBrush(Brush);
	}

}
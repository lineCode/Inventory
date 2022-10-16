// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemSlotWidget.h"
#include "UI/HBItemVisualWidget.h"
#include "UI/DragDrop/HBItemDragDropOperation.h"
#include "Item/HBInventoryItemInstance.h"
#include "Item/Fragments/HBItemVisualFragment.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

UHBItemSlotWidget::UHBItemSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}


void UHBItemSlotWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UHBItemSlotContainerWidget::NativeConstruct()"));
	SetVisibility(ESlateVisibility::Visible);
}

void UHBItemSlotWidget::SetItemData(FInventoryEntity NewItemData)
{
	InventoryEntity = NewItemData;

	check(InventoryEntity.StackCount > 0);

	UHBItemVisualWidget* ItemVisual = WidgetTree->ConstructWidget<UHBItemVisualWidget>(ItemVisualSubclass, TEXT("ItemVisualWidget"));
	MainCanvas->AddChild(ItemVisual);
	ItemVisual->Init(NewItemData);
	ChildItemVisual = ItemVisual;
	SetItemCountText(InventoryEntity.StackCount);

}

void UHBItemSlotWidget::SetSlotEmpty()
{
	InventoryEntity = FInventoryEntity();
	if (ChildItemVisual)
	{
		ChildItemVisual->RemoveFromParent();
	}
	SetItemCountText(0);
}


FReply UHBItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown Clicked To Slot : %s"), *Coordinate.ToString());

	OnSlotClicked.Broadcast(Coordinate);
	return FReply::Handled();
}

void UHBItemSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

bool UHBItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UHBItemDragDropOperation* DDOperation = Cast<UHBItemDragDropOperation>(InOperation);

	if (DDOperation->ItemData.StackCount > 0)
	{
		FIntPoint NewIndex = GetCoordinate();
		OnSlotDragOnDrop.Broadcast(DDOperation->ItemData.Coordinates, NewIndex);
	}

	return false;
}

void UHBItemSlotWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	UHBItemDragDropOperation* DDOperation = Cast<UHBItemDragDropOperation>(InOperation);

	if (DDOperation->ItemData.StackCount > 0)
	{
		const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(DDOperation->ItemData.Instance->GetItemDef(), UHBItemVisualFragment::StaticClass()));

		UE_LOG(LogTemp, Warning, TEXT("NativeOnDragEnter %s"), *GetCoordinate().ToString());
		OnSlotDragEnter.Broadcast(GetCoordinate(), ItemVisualFragment->SlotSize);
	}
}

void UHBItemSlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragLeave %s"), *GetCoordinate().ToString());

	UHBItemDragDropOperation* DDOperation = Cast<UHBItemDragDropOperation>(InOperation);

	if (DDOperation->ItemData.StackCount > 0)
	{
		const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(DDOperation->ItemData.Instance->GetItemDef(), UHBItemVisualFragment::StaticClass()));

		OnSlotDragLeave.Broadcast(GetCoordinate(), ItemVisualFragment->SlotSize);
	}
}

void UHBItemSlotWidget::SetToDragState()
{
	BackgroundImage->SetBrushFromTexture(DragBG);
}

void UHBItemSlotWidget::SetToDefaultState()
{
	BackgroundImage->SetBrushFromTexture(DefaultBG);
}

void UHBItemSlotWidget::SetItemCountText(int32 StackCount)
{
	if (StackCount <= 1)
	{
		ItemAmountText->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ItemAmountText->SetVisibility(ESlateVisibility::Visible);
		ItemAmountText->SetText(FText::AsCultureInvariant(FString::FromInt(StackCount)));
	}
}


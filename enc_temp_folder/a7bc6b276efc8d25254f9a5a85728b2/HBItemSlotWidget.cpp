// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemSlotWidget.h"
#include "UI/HBItemVisualWidget.h"
#include "UI/DragDrop/HBItemDragDropOperation.h"
#include "UI/HBItemContainerWidget.h"
#include "Components/TextBlock.h"
#include "Data/HBItemData.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "HBItemObject.h"
#include "Component/HBItemContainerComponent.h"

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

FReply UHBItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("Clicked To Slot : %s"), *Index.ToString());

	OnSlotClicked.Broadcast(Index);
	return FReply::Handled();
}

void UHBItemSlotWidget::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked To Slot : %s"), *Index.ToString());
	OnSlotClicked.Broadcast(Index);
}

void UHBItemSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	//UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));
}

bool UHBItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	//SetToDefaultState();

	UHBItemDragDropOperation* DDOperation = Cast<UHBItemDragDropOperation>(InOperation);

	if (DDOperation->ItemData.Count>0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DDOperation->Item"));

		FIntPoint NewIndex = GetIndex();
		ParentContainer->GetItemContainerComponent()->MoveItem(DDOperation->ItemData.GetIndex(), NewIndex);

		//ParentContainer->GetItemContainerComponent()->MoveItem(DDOperation->Item, SlotIndex);
		//UE_LOG(LogTemp, Warning, TEXT("Item named %s at %s moved to %s"), *DDOperation->Item->GetData()->GetItemName().ToString(), *DDOperation->Item->GetItemCoordinates());
		//*DDOperation->Item->GetData()->GetItemName(), * DDOperation->Item->GetItemCoordinates(), * SlotIndex->ToString()
	}

	return false;
}

void UHBItemSlotWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	UHBItemDragDropOperation* DDOperation = Cast<UHBItemDragDropOperation>(InOperation);

	if (DDOperation->ItemData.Count > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeOnDragEnter %s"), *GetIndex().ToString());
		ParentContainer->MarkSlots(GetIndex(), DDOperation->ItemData.GetSize());
	}
}

void UHBItemSlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragLeave %s"), *GetIndex().ToString());
	ParentContainer->ClearMarkedSlots();
}

void UHBItemSlotWidget::SetToDragState()
{
	BackgroundImage->SetBrushFromTexture(DragBG);
}

void UHBItemSlotWidget::SetToDefaultState()
{
	BackgroundImage->SetBrushFromTexture(DefaultBG);
}

void UHBItemSlotWidget::RefreshItemCountText()
{
	UE_LOG(LogTemp, Warning, TEXT("UHBItemSlotContainerWidget::SetItemAmountText"));
	FItemData* Item = ParentContainer->ItemContainerComponent->FindItemAtIndex(Index);

	int32 Count__ = Item->GetCount();//ItemData.Count;
	SetItemCountText(Count__);
}

void UHBItemSlotWidget::SetItemCountText(int32 Count)
{
	UE_LOG(LogTemp, Warning, TEXT("Count %d"), Count);
	if (Count <= 1)
	{
		ItemAmountText->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ItemAmountText->SetVisibility(ESlateVisibility::Visible);
		ItemAmountText->SetText(FText::AsCultureInvariant(FString::FromInt(Count)));

		//UHBItemSlotContainerWidget* SlotContainer = WidgetTree->ConstructWidget<UHBItemSlotContainerWidget>(ItemSlotSubclass, TEXT("TEST123"));
		//MainCanvas->AddChild(SlotContainer);
	}
}

void UHBItemSlotWidget::SetItemIconBrush()
{
	if (ChildItemVisual)
	{
		ChildItemVisual->SetItemIconBrush(ItemData.GetIcon());
	}
}

void UHBItemSlotWidget::SetSlotEmpty(bool empty)
{
	if (empty)
	{
		//ItemAmountText->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		//ItemAmountText->SetVisibility(ESlateVisibility::HitTestInvisible);
		ItemAmountText->SetText(FText::FromString("s"));

	}
}

void UHBItemSlotWidget::SetItemData(FItemData NewItemData)
{
	ItemData = NewItemData;

	if (NewItemData.Count <=0 )
	{
		if (ChildItemVisual)
		{
			ChildItemVisual->RemoveFromParent();
		}
		UE_LOG(LogTemp, Warning, TEXT("DDOperation->Item"));
		SetItemCountText(0);
		return;
	}

	UHBItemVisualWidget* ItemVisual = WidgetTree->ConstructWidget<UHBItemVisualWidget>(ItemVisualSubclass, TEXT("TEST123"));
	ItemVisual->SetParentSlot(this);
	MainCanvas->AddChild(ItemVisual);

	FIntPoint ItemSize = ItemData.GetSize();
	Cast<UCanvasPanelSlot>(ItemVisual->Slot)->SetSize(FVector2D(64 * ItemSize.Y, 64 * ItemSize.X));
	ItemVisual->SetItemIconBrush(ItemData.GetIcon());
	ChildItemVisual = ItemVisual;
	SetItemCountText(ItemData.GetCount());
}

//UHBItemData* UHBItemSlotContainerWidget::GetItemData()
//{
//	return ItemObject->GetData();
//}

FItemData UHBItemSlotWidget::GetItemData()
{
	return ItemData;
}

void UHBItemSlotWidget::SetIndex(int x, int y)
{
	Index = FIntPoint(x,y);
}

FIntPoint UHBItemSlotWidget::GetIndex()
{
	return Index;
}

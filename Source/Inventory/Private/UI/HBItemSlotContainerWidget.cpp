// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemSlotContainerWidget.h"
#include "Components/TextBlock.h"
#include "UI/HBItemSlotWidget.h"
#include "Data/HBItemData.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "HBItemObject.h"
#include "UI/HBItemDragDropOperation.h"
#include "UI/HBItemContainerWidget.h"
#include "Component/HBItemContainerComponent.h"

UHBItemSlotContainerWidget::UHBItemSlotContainerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UHBItemSlotWidget> ItemSlotBP(TEXT("WidgetBlueprint'/Game/Demo_/ItemSlotWidget.ItemSlotWidget_C'"));
	ItemSlotSubclass = ItemSlotBP.Class;
}


void UHBItemSlotContainerWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UHBItemSlotContainerWidget::NativeConstruct()"));
	SetVisibility(ESlateVisibility::Visible);
}

FReply UHBItemSlotContainerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("Clicked To Slot : %s"), *Index.ToString());

	OnSlotClicked.Broadcast(Index);
	return FReply::Handled();
}

void UHBItemSlotContainerWidget::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked To Slot : %s"), *Index.ToString());
	OnSlotClicked.Broadcast(Index);
}

void UHBItemSlotContainerWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	//UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));
}

bool UHBItemSlotContainerWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

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

void UHBItemSlotContainerWidget::SetItemAmountText()
{

	int32 Count = ParentContainer->ItemContainerComponent->FindItemAtIndex(Index)->GetCount();//ItemData.Count;

	if (Count ==0)
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

void UHBItemSlotContainerWidget::SetItemIconBrush()
{
	if (OwnItemSlot)
	{
		OwnItemSlot->SetItemIconBrush(ItemData.GetIcon());
	}
}

void UHBItemSlotContainerWidget::SetSlotEmpty(bool empty)
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

void UHBItemSlotContainerWidget::SetItemData(FItemData NewItemData)
{
	if (NewItemData.Count <=0 )
	{
		if (OwnItemSlot)
		{
			OwnItemSlot->RemoveFromParent();
		}
		return;
	}

	ItemData = NewItemData;


	UHBItemSlotWidget* ItemSlot = WidgetTree->ConstructWidget<UHBItemSlotWidget>(ItemSlotSubclass, TEXT("TEST123"));
	ItemSlot->ParentWidget = this;
	MainCanvas->AddChild(ItemSlot);

	FIntPoint Size = ItemData.GetSize();
	Cast<UCanvasPanelSlot>(ItemSlot->Slot)->SetSize(FVector2D(64* Size.Y, 64* Size.X));
	ItemSlot->SetItemIconBrush(ItemData.GetIcon());
	OwnItemSlot = ItemSlot;
	SetItemAmountText();
}

//UHBItemData* UHBItemSlotContainerWidget::GetItemData()
//{
//	return ItemObject->GetData();
//}

FItemData UHBItemSlotContainerWidget::GetItemData()
{
	return ItemData;
}

void UHBItemSlotContainerWidget::SetIndex(int x, int y)
{
	Index = FIntPoint(x,y);
}

FIntPoint UHBItemSlotContainerWidget::GetIndex()
{
	return Index;
}

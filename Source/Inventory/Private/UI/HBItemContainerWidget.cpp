// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemContainerWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Component/HBItemContainerComponent.h"
#include "UI/HBItemSlotWidget.h"
UHBItemContainerWidget::UHBItemContainerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UHBItemContainerWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UHBItemContainerWidget::NativeConstruct()"));
}

void UHBItemContainerWidget::InitContainer(UHBItemContainerComponent* InItemContainerComponent)
{
	ItemContainerComponent = InItemContainerComponent;
	SlotGrid->ClearChildren();

	for (size_t i = 0; i < ItemContainerComponent->GetContainerSize().X; i++)
	{
		TArray<class UHBItemSlotWidget*>SlotContainersRow;
		for (size_t j = 0; j < ItemContainerComponent->GetContainerSize().Y; j++)
		{
			FString Base = "ItemSlot";
			Base.Append(FString::FromInt(i)).AppendChar(',').Append(FString::FromInt(j));
			UHBItemSlotWidget* SlotContainer = WidgetTree->ConstructWidget<UHBItemSlotWidget>(ItemSlotBGSubclass, FName(*Base)/*TEXT("Image")*/);
			SlotContainer->OnSlotClicked.AddDynamic(this, &UHBItemContainerWidget::OnSlotClicked);
			SlotContainer->OnSlotDragEnter.AddDynamic(this, &UHBItemContainerWidget::OnSlotDragEnter);
			SlotContainer->OnSlotDragLeave.AddDynamic(this, &UHBItemContainerWidget::OnSlotDragLeave);
			SlotContainer->OnSlotDragOnDrop.AddDynamic(this, &UHBItemContainerWidget::OnSlotDragOnDrop);
			SlotGrid->AddChildToUniformGrid(SlotContainer, i, j);
			SlotContainer->SetCoordinate(FIntPoint(i, j));
			SlotContainersRow.Add(SlotContainer);
		}
	}

	///SET ContainerSize//
	UCanvasPanelSlot* SlotGridSlot = Cast<UCanvasPanelSlot>(SlotGrid->Slot);
	if (SlotGridSlot)
	{
		FVector2D Size;
		Size.X = 64 * ItemContainerComponent->GetContainerSize().Y;
		Size.Y = 64 * ItemContainerComponent->GetContainerSize().X;
		SlotGridSlot->SetSize(Size);
	}
	///////////////

}

void UHBItemContainerWidget::RefreshContainerWidget()
{
	unimplemented();
}

void UHBItemContainerWidget::OnItemDeleted(FIntPoint Coordinate)
{
	if (GetItemSlotAtCoordinate(Coordinate))
	{
		GetItemSlotAtCoordinate(Coordinate)->SetSlotEmpty();
	}
}

void UHBItemContainerWidget::OnItemAdded(FIntPoint Coordinate, FInventoryEntity InventortyEntry)
{
	if (GetItemSlotAtCoordinate(Coordinate))
	{
		GetItemSlotAtCoordinate(Coordinate)->SetItemData(InventortyEntry);
	}
}

void UHBItemContainerWidget::OnCountChanged(FIntPoint Coordinate, int32 StackCount)
{
	//FItemData* Item = ItemContainerComponent->FindItemAtIndex(Index);

	if (GetItemSlotAtCoordinate(Coordinate))
	{
		GetItemSlotAtCoordinate(Coordinate)->SetItemCountText(StackCount);
	}
}

void UHBItemContainerWidget::OnSlotClicked(FIntPoint Index)
{
	//unimplemented();
}

void UHBItemContainerWidget::OnSlotDragEnter(FIntPoint Index, FIntPoint Size)
{
	MarkSlots(Index, Size);
}

; void UHBItemContainerWidget::OnSlotDragLeave(FIntPoint Index, FIntPoint Size)
{
	ClearMarkedSlots();
}

void UHBItemContainerWidget::OnSlotDragOnDrop(FIntPoint OldCoordinate, FIntPoint NewCoordinate)
{
	if (ItemContainerComponent)
	{
		ItemContainerComponent->MoveItem(OldCoordinate, NewCoordinate);
	}

	ClearMarkedSlots();
}

UHBItemSlotWidget* UHBItemContainerWidget::GetItemSlotAtCoordinate(FIntPoint Coordinate)
{
	FIntPoint Size = ItemContainerComponent->GetContainerSize();
	UWidget* Widget = SlotGrid->GetChildAt(Size.Y * Coordinate.X + Coordinate.Y);
	if (Widget)
	{
		return Cast<UHBItemSlotWidget>(Widget);
	}

	return nullptr;
}

UHBItemSlotWidget* UHBItemContainerWidget::GetItemSlotAtCoordinateOffset(FIntPoint Coordinate, FIntPoint Offset)
{
	Coordinate += Offset;
	return GetItemSlotAtCoordinate(Coordinate);
}

void UHBItemContainerWidget::MarkSlots(FIntPoint Coordinate , FIntPoint Size)
{
	for (size_t X = 0; X < Size.X; X++)
	{
		for (size_t Y = 0; Y < Size.Y; Y++)
		{
			UHBItemSlotWidget* OffSlot = GetItemSlotAtCoordinateOffset(Coordinate, FIntPoint(X,Y));
			if (OffSlot)
			{
				OffSlot->SetToDragState();
				DirtMarkedSlots.Add(OffSlot);
			}
		}		
	}
}

void UHBItemContainerWidget::ClearMarkedSlots()
{
	for (UHBItemSlotWidget* DirtySlot : DirtMarkedSlots)
	{
		DirtySlot->SetToDefaultState();
	}

	DirtMarkedSlots.Empty();
}

//UHBItemContainerComponent* UHBItemContainerWidget::GetItemContainerComponent()
//{
//	return ItemContainerComponent;
//}




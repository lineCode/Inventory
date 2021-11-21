// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemVisualWidget.h"
#include "UI/DragDrop/HBItemDragVisual.h"
#include "UI/DragDrop/HBItemDragDropOperation.h"
#include "UI/HBItemSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Data/HBItemData.h"
#include "Components/Image.h"

void UHBItemVisualWidget::SetParentSlot(class UHBItemSlotWidget* NewParentSlot)
{
	ParentSlot = NewParentSlot;
}

FItemData UHBItemVisualWidget::GetData()
{
	return ParentSlot->GetItemData();
}

void UHBItemVisualWidget::SetItemIconBrush(UTexture2D* Texture)
{
	ItemIcon->SetBrushFromTexture(Texture);
}

FReply UHBItemVisualWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("draggable NativeOnMouseButtonDown"));
	Super::OnMouseButtonDown(InGeometry, InMouseEvent).NativeReply;

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UHBItemVisualWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::OnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//TSubclassOf<UHBItemDragVisual> ClassOfItemDragVisual = LoadClass<UHBItemDragVisual>(NULL, TEXT("WidgetBlueprint'/Game/Demo_/WItemDragVisual.WItemDragVisual_C'"));
	UHBItemDragVisual* ItemDragVisual = CreateWidget<UHBItemDragVisual>(GetWorld(), ClassOfItemDragVisual);

	if (ItemDragVisual)
	{
		FItemData ItemData = GetData();
		//UGameplayStatics::PlaySound2D(GetWorld(), ParentWidget->ParentContainer->Sound, 1, 1);
		OutOperation = Cast<UHBItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UHBItemDragDropOperation::StaticClass()));
		OutOperation->DefaultDragVisual = ItemDragVisual;
		OutOperation->Pivot = EDragPivot::CenterCenter;
		Cast<UHBItemDragDropOperation>(OutOperation)->ItemData = ItemData;
		
		FIntPoint ItemSize = ItemData.GetSize();
		ItemDragVisual->SetSize(FVector2D(64 * ItemSize.Y, 64 * ItemSize.X));
		ItemDragVisual->SetImage(ItemData.GetIcon());
		ItemDragVisual->Initialize();
	}
}
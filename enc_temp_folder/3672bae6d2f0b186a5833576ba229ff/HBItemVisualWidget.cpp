// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemVisualWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "UI/DragDrop/HBItemDragVisual.h"
#include "UI/DragDrop/HBItemDragDropOperation.h"
#include "UI/HBItemSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Item/HBInventoryItemInstance.h"
#include "Item/Fragments/HBItemVisualFragment.h"
#include "Main/HBGameInstance.h"



void UHBItemVisualWidget::Init(FInventoryEntity InInventorEntity)
{
	InventorEntity = InInventorEntity;
	const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(InventorEntity.Instance->GetItemDef(), UHBItemVisualFragment::StaticClass()));

	Cast<UCanvasPanelSlot>(Slot)->SetSize(FVector2D(64 * ItemVisualFragment->SlotSize.Y, 64 * ItemVisualFragment->SlotSize.X));
	ItemIcon->SetBrushFromTexture(ItemVisualFragment->ItemInventoryImage);

}


FReply UHBItemVisualWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("draggable NativeOnMouseButtonDown"));
	Super::OnMouseButtonDown(InGeometry, InMouseEvent);


	Cast<UHBGameInstance>(GetGameInstance())->GetSoundManager()->PlayPickSound();

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
FReply UHBItemVisualWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("draggable NativeOnMouseButtonUp"));
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
}

void UHBItemVisualWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::OnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	UE_LOG(LogTemp, Error, TEXT("Drag Operations"));
	UHBItemDragVisual* ItemDragVisual = CreateWidget<UHBItemDragVisual>(GetWorld(), ClassOfItemDragVisual);

	if (ItemDragVisual && InventorEntity.Instance)
	{
		//UGameplayStatics::PlaySound2D(GetWorld(), ParentWidget->ParentContainer->Sound, 1, 1);

		const UHBItemVisualFragment* ItemVisualFragment = Cast<UHBItemVisualFragment>(UHBInventoryFunctionLibrary::FindItemDefinitionFragment(InventorEntity.Instance->GetItemDef(), UHBItemVisualFragment::StaticClass()));

		OutOperation = Cast<UHBItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UHBItemDragDropOperation::StaticClass()));
		OutOperation->DefaultDragVisual = ItemDragVisual;
		OutOperation->Pivot = EDragPivot::TopCenter;
		OutOperation->Offset = FVector2D(0.1f, -0.25f);

		Cast<UHBItemDragDropOperation>(OutOperation)->ItemData = InventorEntity;
		
		FIntPoint ItemSize = ItemVisualFragment->SlotSize;
		ItemDragVisual->SetSize(FVector2D(64 * ItemSize.Y, 64 * ItemSize.X));
		ItemDragVisual->SetImage(ItemVisualFragment->ItemInventoryImage);
		ItemDragVisual->Initialize();
	}
}



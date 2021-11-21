// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"	
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/HBItemSlotContainerWidget.h"
#include "UI/HBItemContainerWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/HBItemSlotWidget.h"
#include "HBItemObject.h"
//#include "UI/HBDraggableItemWidget.h"
#include "UI/DragDrop/HBItemDragVisual.h"
#include "UI/HBItemDragDropOperation.h"
#include "Kismet/GameplayStatics.h"

UHBItemSlotWidget::UHBItemSlotWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{


}




void UHBItemSlotWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();

	DetectDragKey = EKeys::LeftMouseButton;


	//FIntPoint Size = ParentWidget->GetItemData()->GetItemSize();
	//SetSize(FVector2D(64, 64 ));
	//Cast<UCanvasPanelSlot>(this)->SetSize(FVector2D(64 * Size.Y, 64 * Size.X));

	// ItemTitle can be nullptr if we haven't created it in the
	//// Blueprint subclass
	//if (ItemAmountText)
	//{
	//	//ItemAmountText->SetText(FText::FromString(FString::FromInt(Item.Amount)));
	//	ItemAmountText->SetText(FText::FromString("aaa"));
	//}
	if (ItemThumbnailImage)
	{
		/*if (IsValid(ItemData.Thumbnail))
		{
			UE_LOG(LogTemp, Warning, TEXT("OnMouseButtonDown image is valid"));

			//ItemThumbnailImage->SetBrushFromTexture(ItemData.Thumbnail, true);
			FSlateBrush Brush;
			Brush.SetResourceObject(ItemData.Thumbnail);

			//Brush.set
			ItemThumbnailImage->SetBrush(Brush);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OnMouseButtonDown image is not valid"));
		}*/
		//UInventoryBlueprintLibrary::GetInventoryItemDataByRow()
	}
	//ItemButton->OnClicked.AddDynamic(this, &UHBInventorySlot::testFunc);
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
}



void UHBItemSlotWidget::testFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMouseButtonDown"));
}




FReply UHBItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("draggable NativeOnMouseButtonDown"));

	if (ParentWidget)
	{
		//ParentWidget->OnClick();
	}
	
	FReply Local_Reply = Super::OnMouseButtonDown(InGeometry, InMouseEvent).NativeReply;
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DetectDragKey).NativeReply;
}

void UHBItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::OnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));

	
	//TSubclassOf<UHBDraggableItemWidget> ClassOfItemDragDropVisual = LoadClass<UHBDraggableItemWidget>(NULL, TEXT("WidgetBlueprint'/Game/Demo_/ItemDraggableBP.ItemDraggableBP_C'"));
	TSubclassOf<UHBItemDragVisual> ClassOfItemDragVisual = LoadClass<UHBItemDragVisual>(NULL, TEXT("WidgetBlueprint'/Game/Demo_/WItemDragVisual.WItemDragVisual_C'"));
	UHBItemDragVisual* ItemDragVisual = CreateWidget<UHBItemDragVisual>(GetWorld(), ClassOfItemDragVisual);

	if (ItemDragVisual)
	{		
		UGameplayStatics::PlaySound2D(GetWorld(), ParentWidget->ParentContainer->Sound, 1, 1);
		OutOperation = Cast<UHBItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UHBItemDragDropOperation::StaticClass()));
		OutOperation->DefaultDragVisual = ItemDragVisual;
		OutOperation->Pivot = EDragPivot::CenterCenter;
		Cast<UHBItemDragDropOperation>(OutOperation)->ItemData = ParentWidget->GetItemData();
		FIntPoint SizePoint = ParentWidget->GetItemData().GetSize();
		ItemDragVisual->SetSize(FVector2D(SizePoint.Y * 64, SizePoint.X * 64));
		ItemDragVisual->SetImage(ParentWidget->GetItemData().GetIcon());
		ItemDragVisual->Initialize();
	}
}

void UHBItemSlotWidget::SetItemIconBrush(UTexture2D* Texture)
{
	ItemThumbnailImage->SetBrushFromTexture(Texture);
}

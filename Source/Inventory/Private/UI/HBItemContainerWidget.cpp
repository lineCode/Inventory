// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HBItemContainerWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Component/HBItemContainerComponent.h"
#include "UI/HBItemSlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Data/HBItemData.h"

UHBItemContainerWidget::UHBItemContainerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHBItemContainerWidget::NativeConstruct()
{
	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UHBItemContainerWidget::NativeConstruct()"));



}

void UHBItemContainerWidget::InitContainer(UHBItemContainerComponent* _ItemContainerComponent)
{
	ItemContainerComponent = _ItemContainerComponent;



	//UHBItemSlotWidget* HBItemSlotWidget = CreateWidget<UHBItemSlotWidget>(this, UHBItemSlotWidget::StaticClass());
	//UButton* HBItemSlotWidget = CreateWidget<UButton>(this, UButton::StaticClass());

	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());



	for (size_t i = 0; i < ItemContainerComponent->GetContainerSize().X; i++)
	{
		TArray<class UHBItemSlotWidget*>SlotContainersRow;
		for (size_t j = 0; j < ItemContainerComponent->GetContainerSize().Y; j++)
		{
			FString Base = "DragabbleItemSlot";
			Base.Append(FString::FromInt(i));
			Base.AppendChar(',');
			Base.Append(FString::FromInt(j));

			//UHBItemSlotWidget* HBItemSlotWidget = CreateWidget<UHBItemSlotWidget>(this, UHBItemSlotWidget::StaticClass());
			//UHBItemSlotWidget* HBItemSlotWidget = WidgetTree->ConstructWidget<UHBItemSlotWidget>(ItemSlotSubclass, FName(*Base)); // The second parameter is the name and is optional.
			UHBItemSlotWidget* SlotContainer = WidgetTree->ConstructWidget<UHBItemSlotWidget>(ItemSlotBGSubclass, FName(*Base)/*TEXT("Image")*/); // The second parameter is the name and is optional.
			SlotContainer->OnSlotClicked.AddDynamic(this, &UHBItemContainerWidget::OnSlotClicked);
			SlotContainer->ParentContainer = this;
			//HBItemSlotWidget->
			SlotGrid->AddChildToUniformGrid(SlotContainer, i, j);
			SlotContainer->SetIndex(i, j);

			SlotContainersRow.Add(SlotContainer);
			//SlotGrid->AddChildToUniformGrid(HBItemSlotWidget, i, j);

		}
		SlotContainers.Add(SlotContainersRow);
	}
}

void UHBItemContainerWidget::RefreshContainerWidget()
{
	int sizeX = ItemContainerComponent->GetContainerSize().X;
	int sizeY = ItemContainerComponent->GetContainerSize().Y;


	TArray<FItemData*> Items = ItemContainerComponent->GetItems();

	for (size_t i = 0; i < Items.Num(); i++)
	{
		FIntPoint Index = Items[i]->GetIndex();
		//SlotContainers[Index.X][Index.Y]->SetItemData(Items[i]->GetData());
	}

}

void UHBItemContainerWidget::OnItemDeleted(FIntPoint Index)
{
	FIntPoint Test = Index;
	if (SlotContainers[Index.X][Index.Y])
	{
		FItemData ItemData;
		ItemData.Count = 0;
		SlotContainers[Index.X][Index.Y]->SetItemData(ItemData);
	}
}


void UHBItemContainerWidget::OnItemAdded(FIntPoint Index)
{
	FItemData* Item = ItemContainerComponent->FindItemAtIndex(Index);

	SlotContainers[Index.X][Index.Y]->SetItemData(*Item);
}

void UHBItemContainerWidget::OnCountChanged(FIntPoint Index)
{
	FItemData* Item = ItemContainerComponent->FindItemAtIndex(Index);

	SlotContainers[Index.X][Index.Y]->RefreshItemCountText();
}




void UHBItemContainerWidget::OnSlotClicked(FIntPoint Index)
{
	//ItemContainerComponent->DeleteItemAtIndex(Index);

	//UHBItemObject* Item = ItemContainerComponent->FindItemAtIndex(Index);
	//if (Item)
	//{
	//	Item->DeleteItemAtIndex(Index);
	//}
}

UHBItemContainerComponent* UHBItemContainerWidget::GetItemContainerComponent()
{
	return ItemContainerComponent;
}


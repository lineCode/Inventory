// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBDraggableItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBDraggableItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UHBDraggableItemWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemThumbnailImage = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* MainCanvas = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* ItemIcon = nullptr;

	void SetSize(FVector2D Size);
	void SetImage(class UTexture2D* Image);
	
};

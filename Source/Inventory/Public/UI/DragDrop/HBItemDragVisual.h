// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBItemDragVisual.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBItemDragVisual : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemImage = nullptr;

	/*Set Size Of Item Image*/
	void SetSize(FVector2D Size);

	/*Set Item Image Resource*/
	void SetImage(class UTexture2D* ItemImageTexture);

};

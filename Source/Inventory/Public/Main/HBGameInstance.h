// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Manager/HBSoundManager.h"
#include "HBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UHBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init()override;

	UHBGameInstance();

	class AHBSoundManager* GetSoundManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AHBSoundManager> SoundManagerClass;

private:
	class AHBSoundManager* SoundManager;
	
};

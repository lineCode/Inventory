// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Data/HBItemData.h"
#include "HBSoundManager.generated.h"

/**
 * 
 */


UCLASS()
class INVENTORY_API AHBSoundManager : public AActor
{
	GENERATED_BODY()
	
public:

	AHBSoundManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* ItemPickUp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* DefaultDrop = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* ArmorDrop = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* SwordDrop = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* BowDrop = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* GenericPickSound = nullptr;

	void PlayDropSound(TEnumAsByte<EItemType::Type>  ItemType);
	void PlayPickSound();

	//static USoundCue* ItemAudioCue;
	


};

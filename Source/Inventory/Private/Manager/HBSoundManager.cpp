// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HBSoundManager.h"
#include "Kismet/GameplayStatics.h"

AHBSoundManager::AHBSoundManager()
{
	//static ConstructorHelpers::FObjectFinder<USoundCue> ItemCue(TEXT("SoundWave'/Game/Sound/equip_metal_armor.equip_metal_armor'"));
	//ItemAudioCue = ItemCue.Object;
}

void AHBSoundManager::PlayDropSound(TEnumAsByte<EItemType::Type>  ItemType)
{
	USoundWave* SoundToPlay = nullptr;

	switch (ItemType)
	{
	case EItemType::Default:
		SoundToPlay = DefaultDrop;
		break;
	case EItemType::Armor:
		SoundToPlay = ArmorDrop;
		break;
	case EItemType::Sword:
		SoundToPlay = SwordDrop;
		break;
	case EItemType::Bow:
		SoundToPlay = BowDrop;
		break;
	default:
		SoundToPlay = DefaultDrop;
		break;
	}

	if(SoundToPlay)
	UGameplayStatics::PlaySound2D(GetWorld(), SoundToPlay, 1, 1);
}

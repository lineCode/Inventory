// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/HBGameInstance.h"

UHBGameInstance::UHBGameInstance()
{
	//SoundManager = CreateDefaultSubobject<UHBSoundManager>(TEXT("ItemConfig"));
}

void UHBGameInstance::Init()
{
	//SoundManager = NewObject<UHBSoundManager>(this,SoundManagerClass);
	SoundManager = GetWorld()->SpawnActor<AHBSoundManager>(SoundManagerClass);
}

AHBSoundManager* UHBGameInstance::GetSoundManager()
{
	return SoundManager;
}

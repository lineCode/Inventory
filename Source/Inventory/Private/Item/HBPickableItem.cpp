//// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HBPickableItem.h"
#include "Components/BoxComponent.h"
#include "../InventoryCharacter.h"

// Sets default values
AHBPickableItem::AHBPickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemVisual"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	ColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollider"));;
	ColliderComponent->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AHBPickableItem::OnOverlapped);

}

// Called when the game starts or when spawned
void AHBPickableItem::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AHBPickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHBPickableItem::OnOverlapped(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapped"));
	if (Cast<AInventoryCharacter>(OtherActor))
	{
		if (ItemData.Data)
		{
			if (ItemData.Data->Mesh)
			{
				Cast<AInventoryCharacter>(OtherActor)->PickUpItem(ItemData,1);
			}
		}
		
	}


}

void AHBPickableItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (ItemData.Data)
	{
		if (ItemData.Data->Mesh)
		{
			StaticMeshComponent->SetStaticMesh(ItemData.Data->Mesh);
		}
	}

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUpItemActor.h"	
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APickUpItemActor::APickUpItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Rasdasdasoot"));
	SetRootComponent(Root);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("asdasdasd"));
	ItemMesh->SetupAttachment(RootComponent);

	PickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupCollasdasdasider"));
	PickupCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUpItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	//InitPickupItemActor2(CurrentItemData);

	//if (CurrentItemData.Data)
	//{
	//	ItemMesh->SetStaticMesh(CurrentItemData.Data->Mesh);
	//	ItemMesh->SetWorldScale3D(FVector(0.5));
	//}

	//InitPickupItemActor(CurrentItemData);
}

// Called every frame
void APickUpItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpItemActor::InitPickupItemActor(FItemData InItemData)
{
	if (InItemData.Data)
	{
		if (InItemData.Data->Mesh)
		{
			ItemMesh->SetStaticMesh(InItemData.Data->Mesh);
			ItemMesh->SetWorldScale3D(FVector(0.5));
		}
	}
	
}


void APickUpItemActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);


	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APickUpItemActor, mItemData))
	{
		//various uproperty tricks, see link
		
	}

	InitPickupItemActor(mItemData);

	Super::PostEditChangeProperty(e);
}
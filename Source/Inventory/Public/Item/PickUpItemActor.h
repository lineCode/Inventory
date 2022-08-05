// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/HBItemData.h"
#include "PickUpItemActor.generated.h"

UCLASS()
class INVENTORY_API APickUpItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* PickupCollider;

	UPROPERTY(EditAnywhere)
	FItemData CurrentItemData;

	UFUNCTION()
	void InitPickupItemActor(FItemData ItemData);


};

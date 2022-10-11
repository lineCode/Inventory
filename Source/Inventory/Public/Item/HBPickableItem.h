// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/HBItemData.h"
#include "HBPickableItem.generated.h"

UCLASS()
class INVENTORY_API AHBPickableItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* ColliderComponent;
public:	
	// Sets default values for this actor's properties
	AHBPickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapped(AActor* OverlappedActor, AActor* OtherActor);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere)
	FItemData ItemData;

};

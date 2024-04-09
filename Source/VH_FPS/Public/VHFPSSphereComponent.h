// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "VH_FPS/Character/VHCharacter.h"
#include "VHFPSSphereComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AVHCharacter*, PickUpCharacter);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class VH_FPS_API UVHFPSSphereComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Interactions")
	FOnPickUp OnPickUp;

	UVHFPSSphereComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};




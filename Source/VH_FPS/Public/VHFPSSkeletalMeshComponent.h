// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "VH_FPS/Character/VHCharacter.h"
#include "VHFPSSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class VH_FPS_API UVHFPSSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UVHFPSSkeletalMeshComponent();

	AVHCharacter* Character;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "Object")
	void AttachComponentToPlayer(AVHCharacter* TargetCharacter);

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "WeaponSettings")
	FVector GuntipOffset;

	/*
	 * IMC and Actions
	 */

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* FireIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	/*
	 * Animation and Sound
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation and Sound")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation and Sound")
	UAnimMontage* FireAnimation;

	/*
	 * Projectile
	 */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileToSpawn;

};



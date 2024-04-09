// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeEnemy.h"
#include "GameFramework/Actor.h"
#include "VHFPSEnemyManager.generated.h"

UCLASS()
class VH_FPS_API AVHFPSEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVHFPSEnemyManager();

	void IncreaseAmountToSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int AmountToSpawn;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<ACubeEnemy> EnemyClass;

};


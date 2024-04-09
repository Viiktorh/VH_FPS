// Fill out your copyright notice in the Description page of Project Settings.


#include "VHFPSEnemyManager.h"

// Sets default values
AVHFPSEnemyManager::AVHFPSEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmountToSpawn = 10;

}

void AVHFPSEnemyManager::IncreaseAmountToSpawn()
{
	AmountToSpawn++;
}

// Called when the game starts or when spawned
void AVHFPSEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVHFPSEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AmountToSpawn >= 0)
	{
		AmountToSpawn--;
		FVector loc = GetActorLocation();
		//Calculate a random spawn position based on the Manager's location.
		float SpawnX = FMath::RandRange(loc.X + 0.0f, loc.X + 2000.0f);
		float SpawnY = FMath::RandRange(loc.Y + 0.0f, loc.Y + 2000.0f);
		float SpawnZ = loc.Z + 1000.0f;
		FVector SpawnPosition = FVector(SpawnX, SpawnY, SpawnZ);

		GetWorld()->SpawnActor<ACubeEnemy>(EnemyClass, SpawnPosition, FRotator::ZeroRotator);
	}

}


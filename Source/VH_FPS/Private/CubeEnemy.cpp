// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeEnemy.h"

#include "VHFPSEnemyManager.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACubeEnemy::ACubeEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//RootComponent = Mesh;
	//Mesh->SetSimulatePhysics(true);
	////Generate Overlap events for the root component
	//Mesh->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ACubeEnemy::BeginPlay()
{
	Super::BeginPlay();
	//Mesh->SetEnableGravity(true);
	
}

// Called every frame
void ACubeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < -1000.0f)
	{
		
		Destroy();
	}

}

void ACubeEnemy::NotifyActorBeginOverlap(ACharacter* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->GetName() == "Projectile")
	{
		UE_LOG(LogTemp, Warning, TEXT("destroy"));

		Destroy();
	}
}

float ACubeEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}

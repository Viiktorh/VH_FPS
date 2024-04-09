// Fill out your copyright notice in the Description page of Project Settings.



#include "VH_FPS/Public/VHFPSSphereComponent.h"

UVHFPSSphereComponent::UVHFPSSphereComponent()
{
	SphereRadius = 30.f;
}

void UVHFPSSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UVHFPSSphereComponent::OnSphereBeginOverlap);
}

void UVHFPSSphereComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVHCharacter* Character = Cast<AVHCharacter>(OtherActor);
	if (Character != nullptr)
	{
		OnPickUp.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}

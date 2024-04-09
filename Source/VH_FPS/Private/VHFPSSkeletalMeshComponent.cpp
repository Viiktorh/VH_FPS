// Fill out your copyright notice in the Description page of Project Settings.


#include "VH_FPS/Public/VHFPSSkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

UVHFPSSkeletalMeshComponent::UVHFPSSkeletalMeshComponent()
{
	GuntipOffset = FVector(100.f, 0.f, 10.f);
}

void UVHFPSSkeletalMeshComponent::AttachComponentToPlayer(AVHCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasWeapon())
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMeshFPV(), AttachmentRules, FName(TEXT("AttachSocket")));

	Character->SetHasWeapon(true);

	//Adding the Input Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireIMC, 1);
		}
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UVHFPSSkeletalMeshComponent::Fire);
		}
	}
}

void UVHFPSSkeletalMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character == nullptr)
	{
		return;
	}
}

void UVHFPSSkeletalMeshComponent::Fire()
{
	if (ProjectileToSpawn != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(GuntipOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<AActor>(ProjectileToSpawn, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// Play Sound
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	//Play Animation
	if (FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Character->GetMeshFPV()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.0f);
		}
	}
}

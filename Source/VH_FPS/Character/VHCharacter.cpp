// Fill out your copyright notice in the Description page of Project Settings.

#include "VH_FPS/Character/VHCharacter.h"

#include "CheckpointTriggerVolume.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "MySaveGame.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVHCharacter::AVHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Camera Component*/
	FPVCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FPVCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPVCameraComponent->bUsePawnControlRotation = true;

	/*Skeletal Mesh Component*/
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharMesh"));
	FPVMesh->SetupAttachment(FPVCameraComponent);

	saveObj = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	
}


void AVHCharacter::CheckPointSave()
{
	saveObj->PlayerLocation = GetActorLocation();
	saveObj->PlayerRotation = GetActorRotation();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Data saved ... "));
}


void AVHCharacter::InputSave(const FInputActionValue& Value)
{

	
	saveObj->PlayerLocation = GetActorLocation();
	saveObj->PlayerRotation = GetActorRotation();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Data saved ... "));
}

void AVHCharacter::InputLoad(const FInputActionValue& Value)
{

	//UMySaveGame* loadObj = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	if (saveObj) {
		SetActorLocation(saveObj->PlayerLocation);
		SetActorRotation(saveObj->PlayerRotation);
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Data Loaded"));
}
void AVHCharacter::Move(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, TEXT("Triggering the move Function"));

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AVHCharacter::LookAround(const FInputActionValue& Value)
{
	const FVector2D LookAroundVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAroundVector.X);
		AddControllerPitchInput((LookAroundVector.Y));
	}
}

void AVHCharacter::SetHasWeapon(bool bHasNewWeapon)
{
	bHasWeapon = bHasNewWeapon;
}

bool AVHCharacter::GetHasWeapon()
{
	return bHasWeapon;
}

USkeletalMeshComponent* AVHCharacter::GetMeshFPV() const
{
	return FPVMesh; 
}

UCameraComponent* AVHCharacter::GetFPVCameraComponent() const
{
	return FPVCameraComponent;
}

float AVHCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		
	}
	return DamageAmount;
}

// Called when the game starts or when spawned
void AVHCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Adding the Input Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}

}

// Called every frame
void AVHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVHCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVHCharacter::LookAround);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(IA_Load, ETriggerEvent::Started, this, &AVHCharacter::InputLoad);
		EnhancedInputComponent->BindAction(IA_Save, ETriggerEvent::Triggered, this, &AVHCharacter::InputSave);
	}
}


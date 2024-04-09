// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "MySaveGame.h"
#include "GameFramework/Character.h"
#include "VHCharacter.generated.h"

class ACheckpointTriggerVolume;
struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class InputComponent;
class InputAction;

UCLASS()
class VH_FPS_API AVHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVHCharacter();

	void CheckPointSave();
	ACheckpointTriggerVolume* CheckpointTriggerVolume;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 * Components
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FPVCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* FPVMesh;


	/*
	 * Input Mapping Context and Actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	//Load inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Load;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Save;

	UMySaveGame* saveObj;

	void InputLoad(const FInputActionValue& val);
	void InputSave(const FInputActionValue& val);
	void Move(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);

	/*
	 * Weapon
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bHasWeapon = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasWeapon(bool bHasNewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetHasWeapon();

	USkeletalMeshComponent* GetMeshFPV() const;

	UCameraComponent* GetFPVCameraComponent() const;

	/*
	 * Health
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

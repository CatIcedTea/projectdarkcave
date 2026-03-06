#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProjectDarkCave/Player/PlayerStateMachine.h"
#include <Components/PointLightComponent.h>
#include <ProjectDarkCave/InteractableInterface.h>
#include <ProjectDarkCave/Systems/Inventory.h>
#include <ProjectDarkCave/Systems/HealthComponent.h>
#include "PlayerHandler.generated.h"

UCLASS()
class PROJECTDARKCAVE_API APlayerHandler : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	FComponentReference PlayerEquipmentCenterRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	FComponentReference PlayerLightRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttackingRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxStamina = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentMaxStamina = maxStamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentStamina = maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaRegenRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaRegenDelayTime = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaAttackCost = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaBlockingMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaJumpCost = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaSprintCostRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float dodgeForce = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxLightFuel = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentLightFuel = maxLightFuel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float lightFuelConsumptionRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hungerConsumptionRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanDoAction = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLightIsOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLightIsTransitioning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float interactionDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString interactableTooltip = "";

	UFUNCTION(BlueprintCallable)
	bool DecreaseStamina(float value);

	UFUNCTION(BlueprintCallable)
	void AddLightFuel(float value);

	UFUNCTION(BlueprintCallable)
	void RestoreCurrentMaxStamina(float value);


private:
	float currentMovementSpeedMultiplier = 1.0f;

	float baseMovementSpeed;

	float staminaRegenDelayTimer = 0.0f;

	float playerMass;

	FVector currentMovementDirection;

	void TurnToCamera();

	UChildActorComponent* playerEquipmentCenter;
	
	UPointLightComponent* playerLight;

	float cameraYaw;
	float cameraPitch;

	FVector interactionTraceStart;
	FVector interactionTraceEnd;

	IInteractableInterface* DoInteractionTrace();

	IInteractableInterface* currentInteractable;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float lookSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float minPitch = -90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float maxPitch = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float turnSpeed = 0.2f;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraLocation;

	class UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerStateMachine* PlayerStateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventory* PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHealthComponent* PlayerHealthComponent;

	//Default Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* WalkActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CrouchActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DodgeActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UseLightActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Slot1ActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Slot2ActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Slot3ActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Slot4ActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Slot5ActionInput;

	UPROPERTY(EditAnywhere)
	float sprintSpeedMultiplier = 2.0f;

	UPROPERTY(EditAnywhere)
	float walkSpeedMultiplier = 0.5f;

	void HandleMovementCameraTilt(float value);

	void JumpAction(const FInputActionValue& Value);

	void MoveAction(const FInputActionValue& Value);

	void LookAction(const FInputActionValue& Value);

	void SprintAction(const FInputActionValue& Value);

	void WalkAction(const FInputActionValue& Value);

	void CrouchAction(const FInputActionValue& Value);

	void DodgeAction(const FInputActionValue& Value);

	void UseLightAction(const FInputActionValue& Value);

	void InteractAction(const FInputActionValue& Value);

	void Slot1Action(const FInputActionValue& Value);

	void Slot2Action(const FInputActionValue& Value);

	void Slot3Action(const FInputActionValue& Value);

	void Slot4Action(const FInputActionValue& Value);

	void Slot5Action(const FInputActionValue& Value);
};

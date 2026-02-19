#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProjectDarkCave/Player/PlayerStateMachine.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttackingRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxStamina = 20.0f;
	
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
	bool bCanDoAction = true;

	UFUNCTION(BlueprintCallable)
	bool DecreaseStamina(float value);

private:
	float currentMovementSpeedMultiplier = 1.0f;

	float baseMovementSpeed;

	float staminaRegenDelayTimer = 0.0f;

	float playerMass;

	FVector currentMovementDirection;

	virtual void TurnToCamera();

	UChildActorComponent* playerEquipmentCenter;

	float cameraYaw;
	float cameraPitch;

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
};

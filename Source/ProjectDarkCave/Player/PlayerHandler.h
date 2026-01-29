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

private:
	float currentMovementSpeedMultiplier = 1.0f;

	float baseMovementSpeed;

protected:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraLocation;

	class UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(EditAnywhere)
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
};

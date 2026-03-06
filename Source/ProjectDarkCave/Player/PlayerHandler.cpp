#include "ProjectDarkCave/Player/PlayerHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/InputAction.h"
#include <ProjectDarkCave/PickupableItem.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
APlayerHandler::APlayerHandler()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraLocation = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraLocation"));
	CameraLocation->SetupAttachment(RootComponent);
	CameraLocation->TargetArmLength = 0.f;
	CameraLocation->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraLocation, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	CharacterMovementComponent = GetCharacterMovement();

	PlayerStateMachine = CreateDefaultSubobject<UPlayerStateMachine>(TEXT("PlayerStateMachine"));

	PlayerInventory = CreateDefaultSubobject<UInventory>(TEXT("PlayerInventory"));

	PlayerHealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("PlayerHealthComponent"));
	
	cameraYaw = CameraLocation->GetRelativeRotation().Yaw;
	cameraPitch = CameraLocation->GetRelativeRotation().Pitch;
}

// Called when the game starts or when spawned
void APlayerHandler::BeginPlay()
{
	Super::BeginPlay();
	
	//Setup Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	playerMass = CharacterMovementComponent->Mass;

	baseMovementSpeed = CharacterMovementComponent->MaxWalkSpeed;
	playerEquipmentCenter = Cast<UChildActorComponent>(PlayerEquipmentCenterRef.GetComponent(this));
	playerLight = Cast<UPointLightComponent>(PlayerLightRef.GetComponent(this));
}

// Called every frame
void APlayerHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Reset camera tilt if player is not moving
	if(!PlayerStateMachine->IsMoving())
	{
		HandleMovementCameraTilt(0.f);
	}

	//Decrease stamina if sprinting
	if (PlayerStateMachine->IsMoving() && PlayerStateMachine->IsSprinting() && CharacterMovementComponent->IsMovingOnGround())
	{
		DecreaseStamina(staminaSprintCostRate * DeltaTime);

		if (currentStamina <= 0)
		{
			SprintAction(FInputActionValue(false));
		}
	}

	//Handle stamina regen delay timer
	if(staminaRegenDelayTimer > 0)
	{
		staminaRegenDelayTimer -= DeltaTime;
	}

	TurnToCamera();

	//Regenerate stamina if it is not max and the delay timer is done
	if(currentStamina < currentMaxStamina && staminaRegenDelayTimer <= 0)
	{
		float finalStaminaRegenRate = staminaRegenRate;

		if (PlayerStateMachine->IsBlocking())
			finalStaminaRegenRate *= staminaBlockingMultiplier;

		currentStamina += finalStaminaRegenRate * DeltaTime;
		
		if(currentStamina > currentMaxStamina)
		{
			currentStamina = currentMaxStamina;
		}
	}

	if(playerLight->Intensity > 0 && bLightIsOn && !bLightIsTransitioning)
	{
		currentLightFuel -= lightFuelConsumptionRate * DeltaTime;
		playerLight->SetIntensity(currentLightFuel);
		
		if(currentLightFuel <= 0)
		{
			playerLight->SetIntensity(0);
			currentLightFuel = 0;
			bLightIsOn = false;
		}
	}

	if (currentMaxStamina > 0)
	{
		currentMaxStamina -= hungerConsumptionRate * DeltaTime;

		if(currentMaxStamina < 0)
		{
			currentMaxStamina = 0;
		}

		if(currentStamina > currentMaxStamina)
		{
			currentStamina = currentMaxStamina;
		}
	}

	currentInteractable = DoInteractionTrace();

	if(currentInteractable)
	{
		interactableTooltip = "[E] " + currentInteractable->GetInteractableName();
	}
	else
	{
		interactableTooltip = "";
	}
}

// Called to bind functionality to input
void APlayerHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpActionInput, ETriggerEvent::Started, this, &APlayerHandler::JumpAction);
		EnhancedInputComponent->BindAction(MoveActionInput, ETriggerEvent::Triggered, this, &APlayerHandler::MoveAction);
		EnhancedInputComponent->BindAction(MoveActionInput, ETriggerEvent::Completed, this, &APlayerHandler::MoveAction);
		EnhancedInputComponent->BindAction(LookActionInput, ETriggerEvent::Triggered, this, &APlayerHandler::LookAction);
		EnhancedInputComponent->BindAction(SprintActionInput, ETriggerEvent::Started, this, &APlayerHandler::SprintAction);
		EnhancedInputComponent->BindAction(SprintActionInput, ETriggerEvent::Completed, this, &APlayerHandler::SprintAction);
		EnhancedInputComponent->BindAction(WalkActionInput, ETriggerEvent::Started, this, &APlayerHandler::WalkAction);
		EnhancedInputComponent->BindAction(WalkActionInput, ETriggerEvent::Completed, this, &APlayerHandler::WalkAction);
		EnhancedInputComponent->BindAction(CrouchActionInput, ETriggerEvent::Started, this, &APlayerHandler::CrouchAction);
		EnhancedInputComponent->BindAction(DodgeActionInput, ETriggerEvent::Started, this, &APlayerHandler::DodgeAction);
		EnhancedInputComponent->BindAction(UseLightActionInput, ETriggerEvent::Started, this, &APlayerHandler::UseLightAction);
		EnhancedInputComponent->BindAction(InteractActionInput, ETriggerEvent::Started, this, &APlayerHandler::InteractAction);
		EnhancedInputComponent->BindAction(Slot1ActionInput, ETriggerEvent::Started, this, &APlayerHandler::Slot1Action);
		EnhancedInputComponent->BindAction(Slot2ActionInput, ETriggerEvent::Started, this, &APlayerHandler::Slot2Action);
		EnhancedInputComponent->BindAction(Slot3ActionInput, ETriggerEvent::Started, this, &APlayerHandler::Slot3Action);
		EnhancedInputComponent->BindAction(Slot4ActionInput, ETriggerEvent::Started, this, &APlayerHandler::Slot4Action);
		EnhancedInputComponent->BindAction(Slot5ActionInput, ETriggerEvent::Started, this, &APlayerHandler::Slot5Action);
	}
}

void APlayerHandler::HandleMovementCameraTilt(float value)
{
	
	FRotator playerCamRotation = PlayerCamera->GetRelativeRotation();

	FRotator camMovementTilt = FRotator(playerCamRotation.Pitch, playerCamRotation.Yaw, value * 2.f);
	PlayerCamera->SetRelativeRotation(FMath::Lerp(PlayerCamera->GetRelativeRotation(), camMovementTilt, 0.05f));
}

void APlayerHandler::JumpAction(const FInputActionValue& Value)
{
	if (CharacterMovementComponent->CanEverJump() && DecreaseStamina(staminaJumpCost)) {
		Jump();
	}
}

void APlayerHandler::MoveAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if(Value.Get<FVector2D>().IsZero())
		{
			HandleMovementCameraTilt(0.f);
			PlayerStateMachine->SetStateMoving(false);
			currentMovementDirection = FVector::ZeroVector;
			return;
		}

		//Get the 2D vector of Value
		FVector2D MovementVector = Value.Get<FVector2D>() * currentMovementSpeedMultiplier;

		const FRotator Rotation = CameraLocation->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		currentMovementDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;

		HandleMovementCameraTilt(MovementVector.X);

		PlayerStateMachine->SetStateMoving(true);
	}
}

void APlayerHandler::LookAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		//Get the 2D vector of Value
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		//AddControllerYawInput(LookAxisVector.X);
		//AddControllerPitchInput(-LookAxisVector.Y);

		cameraYaw += LookAxisVector.X * lookSensitivity;
		cameraPitch += LookAxisVector.Y * lookSensitivity;
		cameraPitch = FMath::Clamp(cameraPitch, minPitch, maxPitch);

		CameraLocation->SetRelativeRotation(FRotator(cameraPitch, cameraYaw, 0.0f));
	}
}

void APlayerHandler::TurnToCamera()
{
	FRotator cameraRotation = CameraLocation->GetComponentRotation();
	//Lerp equipment to camera rotation
	playerEquipmentCenter->SetWorldRotation(FMath::Lerp(playerEquipmentCenter->GetComponentRotation(), cameraRotation, turnSpeed));
}

IInteractableInterface* APlayerHandler::DoInteractionTrace()
{
	interactionTraceStart = PlayerCamera->GetComponentLocation();
	interactionTraceEnd = interactionTraceStart + PlayerCamera->GetForwardVector() * interactionDistance;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, interactionTraceStart, interactionTraceEnd, ECC_Visibility, params))
	{
		AActor* hitActor = hitResult.GetActor();

		if (hitActor && hitActor->Implements<UInteractableInterface>())
		{
			return Cast<IInteractableInterface>(hitActor);
		}
	}

	return NULL;
}

void APlayerHandler::SprintAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = baseMovementSpeed * sprintSpeedMultiplier;
		PlayerStateMachine->SetStateSprinting(true);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = baseMovementSpeed;
		PlayerStateMachine->SetStateSprinting(false);
	}
}

void APlayerHandler::WalkAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		currentMovementSpeedMultiplier = walkSpeedMultiplier;
		PlayerStateMachine->SetStateWalking(true);
	}
	else
	{
		currentMovementSpeedMultiplier = 1.0f;
		PlayerStateMachine->SetStateWalking(false);
	}
}

void APlayerHandler::CrouchAction(const FInputActionValue& Value)
{
	if (!PlayerStateMachine->IsCrouching())
	{
		Crouch();
		PlayerStateMachine->SetStateCrouching(true);
	}
	else
	{
		UnCrouch();
		PlayerStateMachine->SetStateCrouching(false);
	}
}

void APlayerHandler::DodgeAction(const FInputActionValue& Value)
{
	if (!DecreaseStamina(staminaJumpCost))
		return;

	if(currentMovementDirection.IsZero())
	{
		LaunchCharacter(FVector::ForwardVector * (dodgeForce * CharacterMovementComponent->Mass), true, true);
	}
	else {
		LaunchCharacter(currentMovementDirection.GetSafeNormal() * (dodgeForce * CharacterMovementComponent->Mass), true, true);
	}
}

void APlayerHandler::UseLightAction(const FInputActionValue& Value)
{
}

void APlayerHandler::InteractAction(const FInputActionValue& Value)
{
	IInteractableInterface* interactable = DoInteractionTrace();

	if (interactable)
	{
		if(Cast<APickupableItem>(interactable))
		{
			PlayerInventory->AddItem(Cast<APickupableItem>(interactable));
		}

		interactable->DoInteraction(this);
	}
}

void APlayerHandler::Slot1Action(const FInputActionValue& Value)
{
	if(PlayerInventory->itemArray[0])
	{
		PlayerInventory->UseItem(0);
	}
}

void APlayerHandler::Slot2Action(const FInputActionValue& Value)
{
	if (PlayerInventory->itemArray[1])
	{
		PlayerInventory->UseItem(1);
	}
}

void APlayerHandler::Slot3Action(const FInputActionValue& Value)
{
	if (PlayerInventory->itemArray[2])
	{
		PlayerInventory->UseItem(2);
	}
}

void APlayerHandler::Slot4Action(const FInputActionValue& Value)
{
	if (PlayerInventory->itemArray[3])
	{
		PlayerInventory->UseItem(3);
	}
}

void APlayerHandler::Slot5Action(const FInputActionValue& Value)
{
	if (PlayerInventory->itemArray[4])
	{
		PlayerInventory->UseItem(4);
	}
}

bool APlayerHandler::DecreaseStamina(float value)
{
	if (currentStamina <= 0.0f)
		return false;

	currentStamina -= value;

	if(currentStamina < 0.0f)
		currentStamina = 0.0f;

	staminaRegenDelayTimer = staminaRegenDelayTime;

	return true;
}

void APlayerHandler::AddLightFuel(float value)
{
	currentLightFuel += value;

	if(currentLightFuel > maxLightFuel)
	{
		currentLightFuel = maxLightFuel;
	}

	if(playerLight)
	{
		playerLight->SetIntensity(currentLightFuel);
	}
}

void APlayerHandler::RestoreCurrentMaxStamina(float value)
{
	currentMaxStamina += value;

	if(currentMaxStamina > maxStamina)
	{
		currentMaxStamina = maxStamina;
	}
}


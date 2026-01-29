#include "ProjectDarkCave/Player/PlayerHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

// Called when the game starts or when spawned
void APlayerHandler::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	baseMovementSpeed = CharacterMovementComponent->MaxWalkSpeed;
}

// Called every frame
void APlayerHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerStateMachine->IsMoving())
	{
		HandleMovementCameraTilt(0.f);
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
	Jump();
}

void APlayerHandler::MoveAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if(Value.Get<FVector2D>().IsZero())
		{
			HandleMovementCameraTilt(0.f);
			PlayerStateMachine->SetStateMoving(false);
			return;
		}

		//Get the 2D vector of Value
		FVector2D MovementVector = Value.Get<FVector2D>() * currentMovementSpeedMultiplier;

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
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


#include "ProjectDarkCave/Player/PlayerStateMachine.h"

// Sets default values for this component's properties
UPlayerStateMachine::UPlayerStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerStateMachine::SetState(EPlayerState newState)
{
	CurrentState = newState;
}

void UPlayerStateMachine::SetStateIdle(bool val)
{
	bIsMoving = false;
	bIsWalking = false;
	bIsSprinting = false;
	bIsCrouching = false;
}
void UPlayerStateMachine::SetStateFalling(bool val)
{
	CurrentState = EPlayerState::Falling;
}
void UPlayerStateMachine::SetStateWalking(bool val)
{
	bIsWalking = val;
}
void UPlayerStateMachine::SetStateMoving(bool val)
{
	bIsMoving = val;
}
void UPlayerStateMachine::SetStateSprinting(bool val)
{
	bIsSprinting = val;
}
void UPlayerStateMachine::SetStateCrouching(bool val)
{
	bIsCrouching = val;
}

bool UPlayerStateMachine::IsIdle()
{
	return !bIsMoving && !bIsWalking && !bIsSprinting && !bIsCrouching;
}
bool UPlayerStateMachine::IsFalling()
{
	return CurrentState == EPlayerState::Falling;
}
bool UPlayerStateMachine::IsWalking()
{
	return bIsWalking;
}
bool UPlayerStateMachine::IsMoving()
{
	return bIsMoving;
}
bool UPlayerStateMachine::IsSprinting()
{
	return bIsSprinting;
}
bool UPlayerStateMachine::IsCrouching()
{
	return bIsCrouching;
}

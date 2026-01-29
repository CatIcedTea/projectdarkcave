#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStateMachine.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8 {
	Idle UMETA(DisplayName = "Idle"),
	Falling UMETA(DisplayName = "Falling"),
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running"),
	Sprinting UMETA(DisplayName = "Sprinting"),
	Crouching UMETA(DisplayName = "Crouching")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDARKCAVE_API UPlayerStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsCrouching = false;
	bool bIsMoving = false;
	bool bIsSprinting = false;
	bool bIsWalking = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State Machine")
	EPlayerState CurrentState = EPlayerState::Idle;

	void SetState(EPlayerState newState);

	void SetStateIdle(bool val);
	void SetStateFalling(bool val);
	void SetStateWalking(bool val);
	void SetStateMoving(bool val);
	void SetStateSprinting(bool val);
	void SetStateCrouching(bool val);

	bool IsIdle();
	bool IsFalling();
	bool IsWalking();
	bool IsMoving();
	bool IsSprinting();
	bool IsCrouching();
};

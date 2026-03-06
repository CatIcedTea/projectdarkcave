#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "BP_Enemy.generated.h"

UCLASS()
class PROJECTDARKCAVE_API ABP_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AAIController* AIController;

	class UCharacterMovementComponent* CharacterMovementComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerception;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);
};

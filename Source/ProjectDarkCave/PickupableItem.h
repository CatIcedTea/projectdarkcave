#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
class APlayerHandler;
#include "PickupableItem.generated.h"

UCLASS()
class PROJECTDARKCAVE_API APickupableItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle timerHandle;

	FVector targetPlayerPos;

	void DoPickupLerpToPlayer();
	void DoPickupLerpToPlayer(FVector playerPos);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString itemName = "Item Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float itemWeight = 1.0f;

	virtual void DoInteraction() override;

	virtual void DoInteraction(AActor* actor) override;

	virtual FString GetInteractableName() override;

	virtual void UseEffect(APlayerHandler* player);
};

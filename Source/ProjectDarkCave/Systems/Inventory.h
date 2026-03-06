#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectDarkCave/PickupableItem.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDARKCAVE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxWeight = 35.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString inventoryString = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APickupableItem*> itemArray;

	UFUNCTION(BlueprintCallable)
	void UseItem(int index);

	void UseItem(APickupableItem* item);

	UFUNCTION(BlueprintCallable)
	bool AddItem(APickupableItem* item);

	UFUNCTION(BlueprintCallable)
	void DropItem(APickupableItem* item);

	UFUNCTION(BlueprintCallable)
	void TrashItem(APickupableItem* item);
};

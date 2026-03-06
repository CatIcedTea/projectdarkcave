#pragma once

#include "CoreMinimal.h"
#include "ProjectDarkCave/PickupableItem.h"
#include "ItemLightFuel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDARKCAVE_API AItemLightFuel : public APickupableItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fuelValue = 5.0f;

	virtual void UseEffect(APlayerHandler* player) override;
};

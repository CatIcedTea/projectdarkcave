#pragma once

#include "CoreMinimal.h"
#include "ProjectDarkCave/PickupableItem.h"
#include "ItemFood.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDARKCAVE_API AItemFood : public APickupableItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthRestoreAmount = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaRestoreAmount = 10.0f;

	virtual void UseEffect(APlayerHandler* player) override;
};

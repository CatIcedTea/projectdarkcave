#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDARKCAVE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float maxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentHealth = 100.f;

	UFUNCTION(BlueprintCallable)
	void Heal(float val);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float val);
};

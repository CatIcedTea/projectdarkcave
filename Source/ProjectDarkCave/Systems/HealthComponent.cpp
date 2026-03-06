#include "ProjectDarkCave/Systems/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Heal(float val)
{
	currentHealth += val;

	if(currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}
}

void UHealthComponent::TakeDamage(float val)
{
	currentHealth -= val;

	if(currentHealth <= 0)
	{
		currentHealth = 0;
		this->GetOwner()->Destroy();
	}
}


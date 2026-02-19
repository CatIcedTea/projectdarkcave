#include "ProjectDarkCave/Player/PlayerEquipment.h"

// Sets default values
APlayerEquipment::APlayerEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


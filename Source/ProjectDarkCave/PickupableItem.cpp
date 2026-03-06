// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDarkCave/PickupableItem.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
APickupableItem::APickupableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupableItem::DoInteraction()
{
	Destroy();
}

void APickupableItem::DoInteraction(AActor* actor)
{

	//targetPlayerPos = actor->GetTransform().GetLocation();
	/*
	GetWorldTimerManager().SetTimer(
		timerHandle,
		this,
		&APickupableItem::DoPickupLerpToPlayer,
		0.01f,
		true
	);
	*/

	Destroy();
}

void APickupableItem::DoPickupLerpToPlayer()
{
	/*
	GEngine->AddOnScreenDebugMessage(
		-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
		5.0f,           // TimeToDisplay: How many seconds to display the message
		FColor::Green,   // DisplayColor: The color of the text
		GetActorLocation().ToString(),      // DebugMessage: The message to display as an FString
		true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
		FVector2D(1.f, 1.f) // TextScale: Optional text scaling
	);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
	}

	Destroy();*/
}


FString APickupableItem::GetInteractableName()
{
	return itemName;
}

void APickupableItem::UseEffect(APlayerHandler* player)
{
	GEngine->AddOnScreenDebugMessage(
		-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
		5.0f,           // TimeToDisplay: How many seconds to display the message
		FColor::Green,   // DisplayColor: The color of the text
		"Used Test Item",      // DebugMessage: The message to display as an FString
		true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
		FVector2D(1.f, 1.f) // TextScale: Optional text scaling
	);
}

void APickupableItem::DoPickupLerpToPlayer(FVector playerPos)
{
}


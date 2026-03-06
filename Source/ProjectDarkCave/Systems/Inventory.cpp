#include "ProjectDarkCave/Systems/Inventory.h"
#include "ProjectDarkCave/Player/PlayerHandler.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	inventoryString = "Inventory: \n";
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventory::UseItem(int index)
{
	UseItem(itemArray[index]);

	itemArray.RemoveAt(index);

	inventoryString = "Inventory: \n";

	for (int k = 0; k < itemArray.Num(); k++)
	{
		inventoryString += "[" + FString::FromInt(k + 1) + "] " + itemArray[k]->GetInteractableName();

		if (k != itemArray.Num() - 1)
			inventoryString += ", ";
	}
}

void UInventory::UseItem(APickupableItem* item)
{
	item->UseEffect(Cast<APlayerHandler>(GetOwner()));
}

bool UInventory::AddItem(APickupableItem* item)
{
	if (itemArray.Num() < 5)
	{
		itemArray.Add(item);

		inventoryString = "Inventory: \n";

		for (int k = 0; k < itemArray.Num(); ++k)
		{
			inventoryString += "[" + FString::FromInt(k + 1) + "] " + itemArray[k]->GetInteractableName();

			if (k != itemArray.Num() - 1)
				inventoryString += ", ";
		}

		return true;
	}

	GEngine->AddOnScreenDebugMessage(
		-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
		5.0f,           // TimeToDisplay: How many seconds to display the message
		FColor::Red,   // DisplayColor: The color of the text
		"Inventory Full",      // DebugMessage: The message to display as an FString
		true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
		FVector2D(1.f, 1.f) // TextScale: Optional text scaling
	);

	return false;
}

void UInventory::DropItem(APickupableItem* item)
{
}

void UInventory::TrashItem(APickupableItem* item)
{
}


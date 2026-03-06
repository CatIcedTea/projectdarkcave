#include "ProjectDarkCave/Items/ItemLightFuel.h"
#include "ProjectDarkCave/Player/PlayerHandler.h"

void AItemLightFuel::UseEffect(APlayerHandler* player)
{
	player->AddLightFuel(fuelValue);
}

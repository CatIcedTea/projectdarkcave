#include "ProjectDarkCave/Items/ItemFood.h"
#include "ProjectDarkCave/Player/PlayerHandler.h"

void AItemFood::UseEffect(APlayerHandler* player)
{
	player->RestoreCurrentMaxStamina(staminaRestoreAmount);
}
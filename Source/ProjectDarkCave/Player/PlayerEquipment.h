#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerEquipment.generated.h"

UCLASS()
class PROJECTDARKCAVE_API APlayerEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

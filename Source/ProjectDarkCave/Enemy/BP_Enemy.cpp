#include "ProjectDarkCave/Enemy/BP_Enemy.h"
#include "AIController.h"
#include "Engine/Engine.h"

// Sets default values
ABP_Enemy::ABP_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	CharacterMovementComponent = GetCharacterMovement();
}

// Called when the game starts or when spawned
void ABP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	if(AIPerception)
	{
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABP_Enemy::OnTargetPerceptionUpdated);
		AIPerception->OnTargetPerceptionForgotten.AddDynamic(this, &ABP_Enemy::OnTargetPerceptionForgotten);
	}

	AIController = Cast<AAIController>(GetController());
}

// Called every frame
void ABP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABP_Enemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag("Player"))
	{
		if (Stimulus.WasSuccessfullySensed()) {
			GEngine->AddOnScreenDebugMessage(
				-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
				5.0f,           // TimeToDisplay: How many seconds to display the message
				FColor::Cyan,   // DisplayColor: The color of the text
				"Found Player",      // DebugMessage: The message to display as an FString
				true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
				FVector2D(1.f, 1.f) // TextScale: Optional text scaling
			);
		}
		else {
			GEngine->AddOnScreenDebugMessage(
				-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
				5.0f,           // TimeToDisplay: How many seconds to display the message
				FColor::Cyan,   // DisplayColor: The color of the text
				"Lost Player",      // DebugMessage: The message to display as an FString
				true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
				FVector2D(1.f, 1.f) // TextScale: Optional text scaling
			);
		}
	}
	
}

void ABP_Enemy::OnTargetPerceptionForgotten(AActor* Actor)
{
	if (Actor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,             // Key: A unique integer key to prevent the same message from being added multiple times (use -1 to always add a new message)
			5.0f,           // TimeToDisplay: How many seconds to display the message
			FColor::Cyan,   // DisplayColor: The color of the text
			"Forgot Player",      // DebugMessage: The message to display as an FString
			true,           // bNewerOnTop: Whether newer messages appear on top (only works with Key == -1)
			FVector2D(1.f, 1.f) // TextScale: Optional text scaling
		);
	}
}


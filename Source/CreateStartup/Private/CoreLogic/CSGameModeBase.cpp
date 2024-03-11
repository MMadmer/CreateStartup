// Create startup game. All rights reserved.


#include "CoreLogic/CSGameModeBase.h"

#include "CoreLogic/Player/CSPlayer.h"
#include "CoreLogic/Player/CSPlayerController.h"
#include "UserInterface/CSHUD.h"
#include "Kismet/GameplayStatics.h"

ACSGameModeBase::ACSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultPawnClass = ACSPlayer::StaticClass();
	PlayerControllerClass = ACSPlayerController::StaticClass();
	HUDClass = ACSHUD::StaticClass();
}

ACSGameModeBase* ACSGameModeBase::GetCSGameMode(const UObject* WorldContextObject)
{
	return Cast<ACSGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

void ACSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

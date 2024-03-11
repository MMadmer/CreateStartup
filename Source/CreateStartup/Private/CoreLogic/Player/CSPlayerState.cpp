// Create startup game. All rights reserved.


#include "CoreLogic/Player/CSPlayerState.h"

ACSPlayerState::ACSPlayerState()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
}

void ACSPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

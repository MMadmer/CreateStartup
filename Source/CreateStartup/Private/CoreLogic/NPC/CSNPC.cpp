// Create startup game. All rights reserved.


#include "CoreLogic/NPC/CSNPC.h"

ACSNPC::ACSNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void ACSNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Create startup game. All rights reserved.


#include "CoreLogic/NPC/CSNPC.h"

ACSNPC::ACSNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MaxSpeed = 0;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMeshComponent);
}

void ACSNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ACSNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


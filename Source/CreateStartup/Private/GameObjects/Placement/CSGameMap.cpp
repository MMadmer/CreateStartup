// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSGameMap.h"

ACSGameMap::ACSGameMap()
{
	PrimaryActorTick.bCanEverTick = false;

	BasePlane = CreateDefaultSubobject<UStaticMeshComponent>("BasePlane");
	SetRootComponent(BasePlane);
	GameMap = CreateDefaultSubobject<UStaticMeshComponent>("GameMap");
	GameMap->AttachToComponent(BasePlane, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACSGameMap::BeginPlay()
{
	Super::BeginPlay();
}

void ACSGameMap::SpawnObjects()
{
	for (const auto& PlacementObject : PlacementObjects)
	{
		ACSPlacementObject::SpawnAttachedObjects(GameMap, PlacementObject);
	}
}

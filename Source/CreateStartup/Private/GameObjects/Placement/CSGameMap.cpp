// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSGameMap.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"

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
	for (const auto& StaticPlacementObject : StaticPlacementObjects)
	{
		ACSPlacementObject::SpawnAttachedObjectsStatic(GameMap, ACSPlacementObject::StaticClass(),
		                                               StaticPlacementObject);
	}
}

void ACSGameMap::StaticActorsToMap() const
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), Actors);

	for (auto& Actor : Actors)
	{
		Actor = Cast<AStaticMeshActor>(Actor);
		if (!Actor) continue;

		const UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(
			Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (!MeshComp) continue;

		const auto Socket = NewObject<UStaticMeshSocket>(GameMap->GetStaticMesh());
		Socket->Tag = MeshComp->GetStaticMesh()->GetName();
		Socket->SocketName = TEXT("%s", );
		GameMap->GetStaticMesh()->Sockets.Add(Socket);
	}
}

void ACSGameMap::RemoveSockets() const
{
	GameMap->GetStaticMesh()->Sockets.RemoveAll([](UStaticMeshSocket* Item) { return true; });
}

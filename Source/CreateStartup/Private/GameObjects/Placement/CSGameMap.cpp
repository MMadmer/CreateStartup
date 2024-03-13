// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSGameMap.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMeshSocket.h"
#include "Interface/CSEditorTools.h"
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
	for (const auto& StaticPlacementObject : PlacementObjects)
	{
		if (const auto& SpecialClass = PlacementSpecial.Find(StaticPlacementObject))
		{
			ACSPlacementObject::SpawnAttachedObjectsStatic(GameMap, *SpecialClass, StaticPlacementObject);
		}
		else
		{
			ACSPlacementObject::SpawnAttachedObjectsStatic(GameMap, ACSPlacementObject::StaticClass(),
			                                               StaticPlacementObject);
		}
	}
}

void ACSGameMap::BakeLevelToMap()
{
#if WITH_EDITORONLY_DATA
	// Clearing map before update
	ClearMap();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	int Counter = 0;

	for (const auto& Actor : Actors)
	{
		UStaticMesh* ActorMesh;

		if (Cast<AStaticMeshActor>(Actor))
		{
			const UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(
				Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			if (!MeshComp) continue;

			ActorMesh = MeshComp->GetStaticMesh();
		}
		else
		{
			ActorMesh = Actor->Implements<UCSEditorTools>() ? ICSEditorTools::Execute_GetMesh(Actor) : nullptr;
		}
		if (!ActorMesh) continue;

		if (Cast<ACSPlacementObject>(Actor))
		{
			PlacementSpecial.Add(ActorMesh, Actor->GetClass());
		}

		const auto Socket = NewObject<UStaticMeshSocket>(GameMap->GetStaticMesh());
		Socket->Tag = ActorMesh->GetName();
		Socket->SocketName = FName(*FString::Printf(TEXT("Generated_%i"), Counter));

		FTransform MapTransform = GetActorTransform();
		FTransform SocketTransform = Actor->GetActorTransform().GetRelativeTransform(MapTransform);
		SocketTransform.SetLocation(
			SocketTransform.GetLocation() - 4.0f * FVector(0.0f, 0.0f, GameMap->Bounds.BoxExtent.Z));

		Socket->RelativeLocation = SocketTransform.GetLocation();
		Socket->RelativeRotation = SocketTransform.Rotator();
		Socket->RelativeScale = SocketTransform.GetScale3D();
		Socket->PreviewStaticMesh = ActorMesh;
		GameMap->GetStaticMesh()->Sockets.Add(Socket);

		PlacementObjects.AddUnique(ActorMesh);

		Counter++;
	}
#endif
}

void ACSGameMap::ClearMap()
{
#if WITH_EDITORONLY_DATA
	PlacementSpecial.Empty();
	PlacementObjects.Empty();
	GameMap->GetStaticMesh()->Sockets.Empty();
#endif
}

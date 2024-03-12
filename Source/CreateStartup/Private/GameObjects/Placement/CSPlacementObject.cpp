// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSPlacementObject.h"

#include "Engine/StaticMeshSocket.h"

ACSPlacementObject::ACSPlacementObject()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

UStaticMesh* ACSPlacementObject::GetMesh_Implementation()
{
	return StaticMesh->GetStaticMesh();
}

void ACSPlacementObject::SetMesh_Implementation(UStaticMesh* NewMesh)
{
	StaticMesh->SetStaticMesh(NewMesh);
}

void ACSPlacementObject::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ACSPlacementObject*> ACSPlacementObject::SpawnAttachedObjects(UStaticMeshComponent* TargetComponent,
                                                                     const TSubclassOf<ACSPlacementObject>& ObjectClass)
{
	TArray<ACSPlacementObject*> SpawnedObjects;

	if (!TargetComponent) return SpawnedObjects;
	if (!TargetComponent->GetStaticMesh()) return SpawnedObjects;

	const FString ObjectTargetSocket = Cast<ACSPlacementObject>(ObjectClass->GetDefaultObject())->TargetSocketTag.
		ToString();

	for (const auto& Socket : TargetComponent->GetStaticMesh()->Sockets)
	{
		if (Socket->Tag.Compare(ObjectTargetSocket, ESearchCase::IgnoreCase) != 0) continue;

		const auto NewObject = TargetComponent->GetWorld()->SpawnActor<ACSPlacementObject>(ObjectClass);
		if (!NewObject) continue;

		NewObject->SetOwner(TargetComponent->GetOwner());
		NewObject->AttachToComponent(TargetComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false),
		                             Socket->SocketName);

		SpawnedObjects.Add(NewObject);
	}

	return SpawnedObjects;
}

TArray<ACSPlacementObject*> ACSPlacementObject::SpawnAttachedObjectsStatic(UStaticMeshComponent* TargetComponent,
                                                                           const TSubclassOf<ACSPlacementObject>&
                                                                           ObjectClass, UStaticMesh* NewMesh)
{
	TArray<ACSPlacementObject*> SpawnedObjects;

	if (!TargetComponent) return SpawnedObjects;
	if (!TargetComponent->GetStaticMesh()) return SpawnedObjects;

	const FString ObjectTargetSocket = NewMesh->GetName();

	for (const auto& Socket : TargetComponent->GetStaticMesh()->Sockets)
	{
		if (Socket->Tag.Compare(ObjectTargetSocket, ESearchCase::IgnoreCase) != 0) continue;

		const auto NewObject = TargetComponent->GetWorld()->SpawnActor<ACSPlacementObject>(ObjectClass);
		if (!NewObject) continue;

		NewObject->SetOwner(TargetComponent->GetOwner());
		NewObject->AttachToComponent(TargetComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false),
		                             Socket->SocketName);
		if (NewMesh) NewObject->StaticMesh->SetStaticMesh(NewMesh);

		SpawnedObjects.Add(NewObject);
	}

	return SpawnedObjects;
}

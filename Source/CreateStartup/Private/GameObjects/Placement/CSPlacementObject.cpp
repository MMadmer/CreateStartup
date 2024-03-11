// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSPlacementObject.h"

ACSPlacementObject::ACSPlacementObject()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ACSPlacementObject::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ACSPlacementObject*> ACSPlacementObject::SpawnAttachedObjects(USceneComponent* TargetComponent,
                                                                     const TSubclassOf<ACSPlacementObject>& ObjectClass)
{
	TArray<ACSPlacementObject*> SpawnedObjects;

	if (!TargetComponent) return SpawnedObjects;

	const FString ObjectTargetSocket = Cast<ACSPlacementObject>(ObjectClass->GetDefaultObject())->TargetSocketPrefix.
		ToString();

	for (const auto& Socket : TargetComponent->GetAllSocketNames())
	{
		if (!Socket.ToString().StartsWith(ObjectTargetSocket)) continue;

		const auto NewObject = TargetComponent->GetWorld()->SpawnActor<ACSPlacementObject>(ObjectClass);
		if (!NewObject) continue;

		NewObject->SetOwner(TargetComponent->GetOwner());
		NewObject->AttachToComponent(TargetComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false),
		                             Socket);

		SpawnedObjects.Add(NewObject);
	}

	return SpawnedObjects;
}

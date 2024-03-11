// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CSPlacementObject.h"
#include "GameFramework/Actor.h"
#include "CSGameMap.generated.h"

UCLASS()
class CREATESTARTUP_API ACSGameMap : public AActor
{
	GENERATED_BODY()

public:
	ACSGameMap();

protected:
	/** Will be placed on tracked geometry. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* BasePlane;

	/** Game map basis. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* GameMap;

	/** Array of classes of objects that map will try to generate. */
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ACSPlacementObject>> PlacementObjects;

	virtual void BeginPlay() override;

	/** Tries to spawn objects from PlacementObjects classes(if target sockets into GameMap mesh exist) */
	UFUNCTION()
	void SpawnObjects();
};

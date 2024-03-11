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
	UPROPERTY(EditDefaultsOnly, meta=(Category="Placement"))
	TArray<TSubclassOf<ACSPlacementObject>> PlacementObjects;

	/** Map of static CSPlacementObject objects that will be just spawn on the game map. */
	UPROPERTY(EditDefaultsOnly, meta=(Category="Placement"))
	TArray<UStaticMesh*> StaticPlacementObjects;

	virtual void BeginPlay() override;

	/** Tries to spawn objects from PlacementObjects classes(if target sockets into GameMap mesh exist) */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Spawn, Objects, Object"))
	void SpawnObjects();

	/** Scan level actors and add them to the GameMap static mesh asset. */
	UFUNCTION(CallInEditor, Category="Editor Tools")
	void StaticActorsToMap() const;
	
	/** Remove all sockets from GameMap static mesh asset. */
	UFUNCTION(CallInEditor, Category="Editor Tools")
	void RemoveSockets() const;
};

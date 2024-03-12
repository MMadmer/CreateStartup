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

	/** Map of special placement classes that will be spawned instead of target static mesh. */
	UPROPERTY(EditAnywhere, meta=(Category="Placement"))
	TMap<UStaticMesh*, TSubclassOf<ACSPlacementObject>> PlacementSpecial;

	/** Array of static CSPlacementObject objects that will be just spawn on the game map. */
	UPROPERTY(EditAnywhere, meta=(Category="Placement"))
	TArray<UStaticMesh*> PlacementObjects;

	virtual void BeginPlay() override;

	/** Tries to spawn objects from PlacementObjects classes(if target sockets into GameMap mesh exist).
	 *	StaticPlacementObjects array will be overwritten.
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Spawn, Objects, Object"))
	void SpawnObjects();

#if WITH_EDITORONLY_DATA
	/** Scan level actors and add them to the GameMap static mesh asset(auto clears the map before scanning). */
	UFUNCTION(CallInEditor, Category="Editor Tools")
	void BakeLevelToMap();

	/** Remove all sockets from GameMap static mesh asset. */
	UFUNCTION(CallInEditor, Category="Editor Tools")
	void ClearMap();
#endif
};

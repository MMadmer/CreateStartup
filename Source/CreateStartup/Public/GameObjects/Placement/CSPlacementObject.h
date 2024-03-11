// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSPlacementObject.generated.h"

UCLASS()
class CREATESTARTUP_API ACSPlacementObject : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	/** Owner's target static mesh socket name prefix(for example, Tree_) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TargetSocketTag;

	ACSPlacementObject();

	/** Tries to spawn objects from target class into each component's socket with compatible prefix. */
	UFUNCTION(BlueprintCallable,
		meta=(ReturnDisplayName="SpawnedObjects", Keywords="Spawn, Attached, Objects, Object, Placement, Place"))
	static TArray<ACSPlacementObject*> SpawnAttachedObjects(UStaticMeshComponent* TargetComponent,
	                                                        const TSubclassOf<ACSPlacementObject>& ObjectClass);

	/** Tries to spawn objects from target class and change static mesh into each component's socket with compatible prefix.
	 *	Will not change the static mesh if nullptr.
	 */
	UFUNCTION(BlueprintCallable, meta=(ReturnDisplayName="SpawnedObjects", Keywords="Spawn, Attached, Actor"))
	static TArray<ACSPlacementObject*> SpawnAttachedObjectsStatic(UStaticMeshComponent* TargetComponent,
	                                                              const TSubclassOf<ACSPlacementObject>& ObjectClass,
	                                                              UStaticMesh* NewMesh = nullptr);

protected:
	virtual void BeginPlay() override;
};

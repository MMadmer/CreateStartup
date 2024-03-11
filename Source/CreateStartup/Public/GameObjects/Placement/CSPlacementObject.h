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
	/** Owner's target static mesh socket name prefix(for example, Tree_) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TargetSocketPrefix;

	ACSPlacementObject();

	/** Tries to spawn objects from target class into each component's socket with compatible prefix. */
	UFUNCTION(BlueprintCallable,
		meta=(ReturnDisplayName="SpawnedObjects", Keywords="Spawn, Attached, Objects, Object, Placement, Place"))
	static TArray<ACSPlacementObject*> SpawnAttachedObjects(USceneComponent* TargetComponent,
	                                                        const TSubclassOf<ACSPlacementObject>&
	                                                        ObjectClass);

protected:
	virtual void BeginPlay() override;
};

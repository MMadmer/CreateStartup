// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CSAnimationComponent.h"
#include "GameObjects/Placement/CSPlacementObject.h"
#include "CSInteractableObject.generated.h"

/**
 * 
 */
UCLASS()
class CREATESTARTUP_API ACSInteractableObject : public ACSPlacementObject
{
	GENERATED_BODY()

protected:
	ACSInteractableObject();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCSAnimationComponent* AnimationComponent;
};

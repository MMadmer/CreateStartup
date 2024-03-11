// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoreLogic/Player/CSPlayerState.h"
#include "CSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CREATESTARTUP_API ACSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACSPlayerController();

	/** Returns CSPlayerState. */
	UFUNCTION(BlueprintPure, meta=(Keywords="Get, CS, Player, State"))
	ACSPlayerState* GetCSPlayerState() const;

	/** Player controller touch event. */
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force,
	                        FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;

private:
	const float TouchTraceLength = 10000.0f;
};

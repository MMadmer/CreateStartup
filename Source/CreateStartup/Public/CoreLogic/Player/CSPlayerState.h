// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CSPlayerState.generated.h"

/**
 * Player statistic class(exists as long as the PlayerController exists)
 */
UCLASS()
class CREATESTARTUP_API ACSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACSPlayerState();

protected:
	virtual void BeginPlay() override;
};

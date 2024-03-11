// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CSGameModeBase.generated.h"

/**
 * Base game mode
 */
UCLASS()
class CREATESTARTUP_API ACSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACSGameModeBase();

	/** Get C++ CSGameModeBase. Return nullptr if current game mode is not a ACSGameModeBase. */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject", Keywords="Get, CS, Game, Mode"))
	static ACSGameModeBase* GetCSGameMode(const UObject* WorldContextObject);

protected:
	virtual void BeginPlay() override;
};

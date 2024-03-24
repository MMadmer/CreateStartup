// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CSAudioSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CREATESTARTUP_API UCSAudioSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Plays cycled level ambient. Songs will not start repeating until the entire array is played back. */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Play, Level, Ambient"))
	void PlayLevelAmbient(UAudioComponent* WorldAmbient, const TSet<USoundBase*> CurrentLevelAmbient,
	                      const float VolumeNorm = 1.0f);

	/** Set new ambient volume multiplier.
	 *  Volume multiplier = base audio component volume * volume normalized.
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Set, Ambient, Volume"))
	void SetAmbientVolume(const float VolumeNorm);

private:
	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY()
	TSet<USoundBase*> LevelAmbient;

	float BaseAudioVolume;
	TSet<int32> Indexes;

	UFUNCTION()
	void CycleAmbient();
};

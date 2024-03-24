// Create startup game. All rights reserved.


#include "CoreLogic/Subsystems/CSAudioSubsystem.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogAudioSys, All, All);

void UCSAudioSubsystem::PlayLevelAmbient(UAudioComponent* WorldAmbient, const TSet<USoundBase*> CurrentLevelAmbient,
                                         const float VolumeNorm)
{
	AudioComponent = WorldAmbient;
	if (!AudioComponent) return;

	// Volume settings
	BaseAudioVolume = AudioComponent->VolumeMultiplier;
	SetAmbientVolume(VolumeNorm);
	
	AudioComponent->OnAudioFinished.AddDynamic(this, &UCSAudioSubsystem::CycleAmbient);

	if (LevelAmbient.Num() > 0) LevelAmbient.Empty();

	LevelAmbient.Append(CurrentLevelAmbient);
	CycleAmbient();
}

void UCSAudioSubsystem::SetAmbientVolume(const float VolumeNorm)
{
	if (!AudioComponent) return;

	AudioComponent->SetVolumeMultiplier(FMath::Clamp(BaseAudioVolume * VolumeNorm, 0.001f, 1.0f));
}

void UCSAudioSubsystem::CycleAmbient()
{
	if (!GetWorld()) return;

	int32 CurrentIndex;

	if (Indexes.Num() >= LevelAmbient.Num()) Indexes.Empty();

	if (LevelAmbient.Num() == 0)
	{
		UE_LOG(LogAudioSys, Warning, TEXT("Ambient not found"));
		return;
	}

	do
	{
		CurrentIndex = FMath::RandRange(0, LevelAmbient.Num() - 1);
	}
	while (Indexes.Contains(CurrentIndex));
	Indexes.Add(CurrentIndex);

	auto SoundIt = LevelAmbient.CreateIterator();
	for (int32 i = 0; i < CurrentIndex; ++i)
	{
		++SoundIt;
	}

	USoundBase* Song = *SoundIt;
	if (!Song) return;

	AudioComponent->SetSound(Song);
	AudioComponent->Play();
	// UE_LOG(LogTemp, Display, TEXT("Ok %s"), *Song->GetName())
}

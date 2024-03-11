// Create startup game. All rights reserved.


#include "CoreLogic/Subsystems/CSARSubsystem.h"
#include "ARBlueprintLibrary.h"

void UCSARSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCSARSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UCSARSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSessionStatus();

	if (bIsScanActive)
	{
		FindImage();
	}
}

FARSessionStatus UCSARSubsystem::GetARSessionStatus()
{
	return UARBlueprintLibrary::GetARSessionStatus();
}

UARSessionConfig* UCSARSubsystem::GetARSessionConfig()
{
	return UARBlueprintLibrary::GetSessionConfig();
}

void UCSARSubsystem::SetIsScanActive(bool Active)
{
	if (bIsScanActive != Active)
	{
		bIsScanActive = Active;
		OnScanActiveChanged.Broadcast(bIsScanActive);
	}
}

void UCSARSubsystem::UpdateSessionStatus()
{
	const EARSessionStatus CurrentSessionStatus = GetARSessionStatus().Status;

	if (CurrentSessionStatus == EARSessionStatus::Running)
	{
		if (!bSessionIsRunning)
		{
			bSessionIsRunning = true;
			OnSessionChanged.Broadcast(bSessionIsRunning, CurrentSessionStatus);
		}
	}
	else
	{
		if (bSessionIsRunning)
		{
			bSessionIsRunning = false;
			OnSessionChanged.Broadcast(bSessionIsRunning, CurrentSessionStatus);
		}
	}
}

void UCSARSubsystem::FindImage() const
{
	auto FoundImages = UARBlueprintLibrary::GetAllGeometriesByClass(UARTrackedImage::StaticClass());
	if (!FoundImages.IsValidIndex(0)) return;

	OnTrackedImageFound.Broadcast(Cast<UARTrackedImage>(FoundImages[0]));
}

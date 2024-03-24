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

void UCSARSubsystem::SetIsScanActive(const bool Active)
{
	if (bIsScanActive != Active)
	{
		bIsScanActive = Active;
		OnScanActiveChanged.Broadcast(bIsScanActive);
	}
}

UARPlaneGeometry* UCSARSubsystem::GetNearestPlaneByLineTrace(const FVector2D& ScreenPoint)
{
	TArray<FARTraceResult> TrackedObjects = UARBlueprintLibrary::LineTraceTrackedObjects(
		ScreenPoint, false, true, true, true);

	return Cast<UARPlaneGeometry>(TrackedObjects.IsValidIndex(0)
		                              ? TrackedObjects[0].GetTrackedGeometry()
		                              : nullptr);
}

TArray<UARPlaneGeometry*> UCSARSubsystem::GetFoundPlanes()
{
	TArray<UARPlaneGeometry*> PlaneGeometries;
	TArray<UARTrackedGeometry*> TrackedGeometries = UARBlueprintLibrary::GetAllGeometriesByClass(
		UARPlaneGeometry::StaticClass());

	for (const auto TrackedGeometry : TrackedGeometries)
	{
		UARPlaneGeometry* PlaneGeometry = Cast<UARPlaneGeometry>(TrackedGeometry);
		if (!PlaneGeometry) continue;

		PlaneGeometries.Add(PlaneGeometry);
	}

	return PlaneGeometries;
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

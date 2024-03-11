// Create startup game. All rights reserved.


#include "CoreLogic/Player/CSPlayerController.h"

ACSPlayerController::ACSPlayerController()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

ACSPlayerState* ACSPlayerController::GetCSPlayerState() const
{
	return Cast<ACSPlayerState>(PlayerState);
}

bool ACSPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force,
                                     FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	const bool Result = Super::InputTouch(Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);

	if (Type == ETouchType::Began || Type == ETouchType::Ended)
	{
		int32 ScreenX = 0;
		int32 ScreenY = 0;
		GetViewportSize(ScreenX, ScreenY);

		FVector ScreenWorldLocation{};
		FVector ScreenWorldDirection{};

		if (DeprojectScreenPositionToWorld(ScreenX, ScreenY, ScreenWorldLocation, ScreenWorldDirection))
		{
			if (GetWorld())
			{
				const FVector StartLocation = ScreenWorldLocation;
				const FVector EndLocation = StartLocation + (ScreenWorldDirection * TouchTraceLength);
				FHitResult HitResult{};

				if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation,
				                                            FCollisionObjectQueryParams::AllObjects))
				{
					switch (Type)
					{
					case ETouchType::Began:
						HitResult.Actor->OnInputTouchBegin.Broadcast(ETouchIndex::Touch1, GetPawn());
						break;
					case ETouchType::Ended:
						HitResult.Actor->OnInputTouchEnd.Broadcast(ETouchIndex::Touch1, GetPawn());
						break;
					default: ;
					}
				}
			}
		}
	}

	return Result;
}

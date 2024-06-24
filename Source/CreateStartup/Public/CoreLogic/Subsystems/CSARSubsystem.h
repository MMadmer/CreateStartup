// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARBlueprintLibrary.h"
#include "CSARSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionChangedSignature,
                                             bool, SessionRunning,
                                             EARSessionStatus, SessionStatus);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScanActiveChangedSignature, bool, IsScanActive);

/**
 * Contains extended information about current AR session.
 */
UCLASS()
class CREATESTARTUP_API UCSARSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Called when session status changes(from running to any or from any to running). */
	UPROPERTY(BlueprintAssignable)
	FOnSessionChangedSignature OnSessionChanged;

	/** Called when scanning status changes(not a session). */
	UPROPERTY(BlueprintAssignable)
	FOnScanActiveChangedSignature OnScanActiveChanged;

	// FTickableGameObject implementation Begin
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCSARSubsystem, STATGROUP_Tickables);
	}

	virtual void Tick(float DeltaTime) override;
	// FTickableGameObject implementation End

	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	/** Get current AR session status. */
	UFUNCTION(BlueprintPure, meta=(Keywords="Get AR Session Status"))
	static FARSessionStatus GetARSessionStatus();

	/** Get current AR session config. */
	UFUNCTION(BlueprintPure, meta=(Keywords="Get AR Session Config"))
	static UARSessionConfig* GetARSessionConfig();

	/** Get is scan active. */
	UFUNCTION(BlueprintPure, meta=(Keywords="Get Is Scan Active"))
	FORCEINLINE bool GetIsScanActive() const { return bIsScanActive; }

	/** Set scanning status(AR session must be running to scan). */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Set Is Scan Active"))
	void SetIsScanActive(const bool Active);

	/** Returns nearest plane(or nullptr) under target screen coordinates. */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Get Nearest Plane By Line Trace"))
	FARTraceResult GetNearestPlaneByLineTrace(const FVector2D& ScreenPoint);
	
	/** Returns all found planes. */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Get Found Planes"))
	TArray<UARPlaneGeometry*> GetFoundPlanes();

protected:
	/** Return current AR session is running or not. */
	UPROPERTY(BlueprintReadOnly)
	bool bSessionIsRunning = false;

	/** Get scanning status(AR session must be running to scan). */
	UPROPERTY(BlueprintReadOnly)
	bool bIsScanActive = false;

	void UpdateSessionStatus();
};

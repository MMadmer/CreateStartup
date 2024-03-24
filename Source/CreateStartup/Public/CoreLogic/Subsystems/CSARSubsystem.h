// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ARBlueprintLibrary.h"
#include "CSARSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionChangedSignature,
                                             bool, SessionRunning,
                                             EARSessionStatus, SessionStatus);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrackedImageFoundSignature, UARTrackedImage*, FoundImage);

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

	/** Called when any AR camera found image(returns first found image from session). */
	UPROPERTY(BlueprintAssignable)
	FOnTrackedImageFoundSignature OnTrackedImageFound;

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
	UFUNCTION(BlueprintPure, meta=(Keywords="Get, AR, Session, Status"))
	static FARSessionStatus GetARSessionStatus();

	/** Get current AR session config. */
	UFUNCTION(BlueprintPure, meta=(Keywords="Get, AR, Session, Config"))
	static UARSessionConfig* GetARSessionConfig();

	/** Set scanning status(AR session must be running to scan). */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Set, Is, Scan, Active"))
	void SetIsScanActive(bool Active);

protected:
	/** Return current AR session is running or not. */
	UPROPERTY(BlueprintReadOnly)
	bool bSessionIsRunning = false;

	/** Get scanning status(AR session must be running to scan). */
	UPROPERTY(BlueprintReadOnly)
	bool bIsScanActive = false;

	void UpdateSessionStatus();
	void FindImage() const;
};

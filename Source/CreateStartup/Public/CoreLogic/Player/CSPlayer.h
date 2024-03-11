// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CSPlayer.generated.h"

class UCameraComponent;

UCLASS()
class CREATESTARTUP_API ACSPlayer : public APawn
{
	GENERATED_BODY()

public:
	ACSPlayer();

	/** Player AR camera. */
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

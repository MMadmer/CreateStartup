// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSNPC.generated.h"

UCLASS()
class CREATESTARTUP_API ACSNPC : public AActor
{
	GENERATED_BODY()

public:
	ACSNPC();
	virtual void Tick(float DeltaTime) override;

protected:
	/** Client money. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Client info", meta=(ClampMin="0.0", UIMin="0.0"))
	float MaxSpeed;

	virtual void BeginPlay() override;
};

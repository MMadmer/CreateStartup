// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSAnimationComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATESTARTUP_API UCSAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCSAnimationComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact", meta=(ClampMin="0.0", UIMin="0.0"))
	float AnimationTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact",
		meta=(ClampMin="0", UIMin="0", ClampMax="120", UIMax="120"))
	int32 AnimationFrameRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact",
		meta=(ClampMin="0.0", UIMin="0.0", ClampMax="0.0", UIMax="0.0"))
	float ScaleAmplitude;

	FVector OriginalScale;
	FScriptDelegate ScriptDelegate;
	int32 TotalFrames;
	int32 CurrentFrame;

	UFUNCTION(BlueprintCallable, Category="Interact")
	void PlayInteractAnim();

	UFUNCTION()
	void InteractAnimFrame();


	virtual void BeginPlay() override;

	FTimerHandle InteractTimerHandle;
};

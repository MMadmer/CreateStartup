// Create startup game. All rights reserved.


#include "Components/CSAnimationComponent.h"

UCSAnimationComponent::UCSAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	AnimationTime = 0.3f;
	AnimationFrameRate = 30;
	ScaleAmplitude = 0.2f;
	TotalFrames = AnimationFrameRate * AnimationTime;
}

void UCSAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalScale = GetOwner()->GetActorScale3D();
	ScriptDelegate.BindUFunction(this, TEXT("PlayInteractAnim"));
	GetOwner()->OnInputTouchBegin.Add(ScriptDelegate);
}

void UCSAnimationComponent::PlayInteractAnim()
{
	CurrentFrame = 0;
	GetOwner()->SetActorScale3D(OriginalScale);
	GetWorld()->GetTimerManager().SetTimer(InteractTimerHandle, this, &UCSAnimationComponent::InteractAnimFrame,
	                                       AnimationTime * (static_cast<float>(1) / static_cast<float>(
		                                       AnimationFrameRate)), true
	);
}

void UCSAnimationComponent::InteractAnimFrame()
{
	CurrentFrame++;
	if (CurrentFrame > TotalFrames)
	{
		if (!GetWorld()) return;;
		GetWorld()->GetTimerManager().ClearTimer(InteractTimerHandle);
		GetOwner()->SetActorScale3D(OriginalScale);
		CurrentFrame = 0;
		return;
	}
	const float SinRes = ScaleAmplitude * FMath::Sin(AnimationFrameRate * AnimationTime * (static_cast<float>(1) / static_cast<float>(AnimationFrameRate)));
	FVector TempScale;
	TempScale.Z = OriginalScale.Z + SinRes;
	TempScale.X = OriginalScale.X - SinRes;
	TempScale.Y = OriginalScale.Y - SinRes;
	GetOwner()->SetActorScale3D(TempScale);
}

// Create startup game. All rights reserved.


#include "CoreLogic/Player/CSPlayer.h"

ACSPlayer::ACSPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
}

void ACSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

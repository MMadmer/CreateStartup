// Create startup game. All rights reserved.


#include "CoreLogic/NPC/CSNPCClient.h"

ACSNPCClient::ACSNPCClient()
{
	Money = 0;
}

void ACSNPCClient::TryTakeMoney(int32& TakenMoney, int32& NotEnough, const int32 MoneyToTake)
{
	if (Money >= MoneyToTake)
	{
		SetMoney(Money -= MoneyToTake);
		TakenMoney = MoneyToTake;
	}
	else
	{
		NotEnough = MoneyToTake - Money;
		TakenMoney = 0;
	}
}

bool ACSNPCClient::SetMoney(const int32 NewMoney)
{
	const bool Success = NewMoney > 0;

	if(Success) Money = NewMoney;

	return Success;
}

void ACSNPCClient::BeginPlay()
{
	Super::BeginPlay();
}

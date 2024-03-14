// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreLogic/NPC/CSNPC.h"
#include "Interface/CSBusiness.h"
#include "CSNPCClient.generated.h"

/**
 * 
 */
UCLASS()
class CREATESTARTUP_API ACSNPCClient : public ACSNPC, public ICSBusiness
{
	GENERATED_BODY()

public:
	ACSNPCClient();

	// Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="Business|Client"))
	void BusinessEntered(ACSInteractableObject* ProductCount);
	void BusinessEntered_Implementation(ACSInteractableObject* ProductCount) override;
	

	/** Tries to take money from client. Not enough will > 0 and money will not be taken if MoneyToTake > than Money. */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Try, Take, Money"))
	void TryTakeMoney(int32& TakenMoney, int32& NotEnough, const int32 MoneyToTake);

protected:
	/** Client's money. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Client info", meta=(ClampMin="0", UIMin="0"))
	int32 Money;

	/** Set new value to money if NewMoney > 0. */
	UFUNCTION(BlueprintCallable, meta=(ReturnDisplayName="Success", BlueprintProtected, Keywords="Set, Money"))
	bool SetMoney(const int32 NewMoney);

	virtual void BeginPlay() override;
};

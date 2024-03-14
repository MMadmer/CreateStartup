// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameObjects/Placement/CSInteractableObject.h"
#include "UObject/Interface.h"
#include "CSBusiness.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCSBusiness : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATESTARTUP_API ICSBusiness
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="Business|Business"))
	int32 UnitPrice();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="Business|Business"))
	void BuyRequest(int32& Cost, int32& ProductNum, int32 Money, int32 ProductCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="Business|Business"))
	void BuyFinished(int32 Money, int32 ProductCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="Business|Client"))
	void BusinessEntered(ACSInteractableObject* ProductCount);
};

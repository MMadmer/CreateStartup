// Create startup game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CSEditorTools.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCSEditorTools : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATESTARTUP_API ICSEditorTools
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="EditorTools"))
	void SetMesh(UStaticMesh* NewMesh);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Category="EditorTools"))
	UStaticMesh* GetMesh();
};

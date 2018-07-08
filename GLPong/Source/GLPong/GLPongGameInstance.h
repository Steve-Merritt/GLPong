// Copyright Steve Merritt 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GLPongGameInstance.generated.h"

class APlayerLocal;

/**
 * 
 */
UCLASS()
class GLPONG_API UGLPongGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	APlayerLocal* PlayerLocal;
	
};

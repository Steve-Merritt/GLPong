// Copyright Steve Merritt 2018

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "PlayerLocal.generated.h"

/**
 * 
 */
UCLASS()
class GLPONG_API APlayerLocal : public APlayerBase
{
	GENERATED_BODY()
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	
};

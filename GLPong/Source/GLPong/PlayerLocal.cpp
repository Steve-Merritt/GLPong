// Copyright Steve Merritt 2018

#include "PlayerLocal.h"
#include "Components/InputComponent.h"

// Called to bind functionality to input
void APlayerLocal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveUp", this, &APlayerBase::MoveUp);
		PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBase::MoveRight);
	}
}



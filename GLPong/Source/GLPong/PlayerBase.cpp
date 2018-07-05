// Copyright Steve Merritt 2018

#include "PlayerBase.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DeltaLocation = Velocity * Speed * DeltaTime;
	AddActorWorldOffset(DeltaLocation, true);
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveUp", this, &APlayerBase::MoveUp);
	}
}

void APlayerBase::MoveUp(float Value)
{
	Velocity = GetActorForwardVector() * Value;
}


// Copyright Steve Merritt 2018

#include "PlayerBase.h"

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
	
	SetStatus(PlayerProperties::Serving);

	Props.x = GetActorLocation().X;
	Props.y = GetActorLocation().Y;
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Velocity = GetActorForwardVector() * UpDelta + GetActorRightVector() * RightDelta;
	Props.LastMoveDelta = Velocity * Speed;

	// Limit paddle movement
	FVector CurrentLocation = GetActorLocation();
	FVector DesiredLocation = CurrentLocation + Props.LastMoveDelta * DeltaTime;
	if (DesiredLocation.Y > -2500)
	{
		DesiredLocation.Y = -2500;
	}
	if (DesiredLocation.Y < -3500)
	{
		DesiredLocation.Y = -3500;
	}

	if (DesiredLocation.X > 520)
	{
		DesiredLocation.X = 520;
	}
	if (DesiredLocation.X < -2740)
	{
		DesiredLocation.X = -2740;
	}

	SetActorLocation(DesiredLocation, true);

	Props.x = GetActorLocation().X;
	Props.y = GetActorLocation().Y;
}

void APlayerBase::MoveUp(float Value)
{
	UpDelta = Value;
}

void APlayerBase::MoveRight(float Value)
{
	RightDelta =  Value;
}

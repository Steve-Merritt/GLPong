// Copyright Steve Merritt 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerBase.generated.h"

struct PlayerProperties
{
	// direction
	enum Direction { Up, Down, Out, In, Stopped };
	uint32 vDir;
	uint32 hDir;
	// status
	enum Status { Serving, Playing, Exploding, Typing };
	uint32 status;
	// position info
	float x;
	float y;
	float xMin, xMax;
	float yMin, yMax;
	// velocity
	float xv;
	float yv;
	float xa, ya;
	float maxSpeed;
	FVector LastMoveDelta;
	bool bIsAlive;
	bool bIsTyping;
};

UCLASS()
class GLPONG_API APlayerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	PlayerProperties GetProps() const { return Props; }
	void SetStatus(PlayerProperties::Status status) { Props.status = status; }

	void MoveUp(float Value);
	void MoveRight(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Velocity;
	float UpDelta;
	float RightDelta;

	UPROPERTY(EditAnywhere)
	float Speed = 8000.0f;

	PlayerProperties Props;
};

// Copyright Steve Merritt 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UGLPongGameInstance;

struct BallProperties
{
	enum HitStatus { HitNothing, HitLeftSide, HitRightSide, HitBottom, HitTop };
	enum Spin { NoSpin, UpSpin, DownSpin };
	enum ActiveStatus { Inactive, Active };
	uint32 spin;
	bool status;
	float x;
	float y;
	float xv;
	float yv;
	float speed;
	float maxSpeed;
	float minSpeed;
	float radius;
};

UCLASS()
class GLPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void  ResetPosition(float bx, float by);
#if 0
	void  Activate() { _bs.status = CBallInfo::Active; }
	void  Deactivate() { _bs.status = CBallInfo::Inactive; }
	bool  IsActive() { return _bs.status; }
	void  SetRadius(float radius) { _radius = radius; }
	void  SetSpeed(float speed) { _bs.speed = speed; }
	float GetRadius() const { return _radius; };
	BallProperties GetProps() { return Props; }
	void  Explode();
	bool  CheckCollision(CBasePlayer *p, float dt);
	void  CollisionResponse(CPlrInfo &ps);
#endif

	UPROPERTY(BlueprintReadWrite)
	UGLPongGameInstance* GameInstance;

private:
	BallProperties Props;

	UFUNCTION()
	void OnBallHitSomething(AActor* OverlapedActor, AActor* OtherActor);
};

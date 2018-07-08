// Copyright Steve Merritt 2018

#include "Ball.h"
#include "Engine/World.h"
#include "GLPongGameInstance.h"
#include "PlayerLocal.h"
#include "GLPongGameInstance.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UGLPongGameInstance>(World->GetGameInstance());
	}

	OnActorBeginOverlap.AddDynamic(this, &ABall::OnBallHitSomething);

	Props.status = BallProperties::Inactive;
	Props.x = GetActorLocation().X;
	Props.y = GetActorLocation().Y;
	Props.radius = 100.0f;
	Props.maxSpeed = 10.0f;
	Props.minSpeed = 2.0f;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GameInstance) return;

	// get player state info
	PlayerProperties P1Props = GameInstance->PlayerLocal->GetProps();
	//UE_LOG(LogTemp, Warning, TEXT("status=%d | x=%f | y=%f"), P1Props.status, P1Props.x, P1Props.y);

	//p2info = p2->GetInfo();

	// no - local machine updates ball		
	if (P1Props.status == PlayerProperties::Serving) {
		// move the ball with the paddle
		//Props.y = P1Props.y + Props.radius * 5;
		//if (P1Props.y > P1Props.yMin && P1Props.y < P1Props.yMax && P1Props.hDir == PlayerProperties::Out) {
		//	// serve the ball
		//	Props.speed = Props.maxSpeed;
		//	Props.y = P1Props.yMax + Props.radius * 2 + 6;
		//	Props.yv = 1.0f;
		//	Props.spin = BallProperties::NoSpin;
		//	GameInstance->PlayerLocal->SetStatus(PlayerProperties::Playing);
		//}
		Props.x = P1Props.x;
	}
#if 0
	else if (p2info.status == PlayerProperties::Serving) {
		// move the ball with the paddle
		Props.x = p2info.x - Props.radius * 2;
		if (p2info.x > p2info.xMin && p2info.x < p2info.xMax && p2info.hDir == PlayerProperties::Out) {
			// serve the ball
			Props.speed = Props.maxSpeed;
			Props.x = p2info.xMin - Props.radius * 2 - 6;
			Props.xv = -1.0f;
			Props.spin = BallProperties::NoSpin;
			p2->SetStatus(PlayerProperties::Playing);
			if (myGame->GetMode() == GM_MP_NET && p2->GetType() == PT_LOCAL_P2) bSendUpdate = true;
		}
		Props.y = p2info.y;
	}
	else {
		// do collision test/response
		if (Props.x < 384) {
			if (CheckCollision(p1, dt)) {
				CollisionResponse(P1Props);
				if (Props.speed > BALL_MAX_SPEED) myGame->sMgr->Play(SFX_PUNCH);
				else myGame->sMgr->Play(SFX_BALL_HIT_PADDLE);
				if (myGame->GetMode() == GM_MP_NET && p1->GetType() == PT_LOCAL_P1) bSendUpdate = true;
			}
		}
		else if (Props.x > 384) {
			if (CheckCollision(p2, dt)) {
				CollisionResponse(p2info);
				if (Props.speed > BALL_MAX_SPEED) myGame->sMgr->Play(SFX_PUNCH);
				else myGame->sMgr->Play(SFX_BALL_HIT_PADDLE);
				if (myGame->GetMode() == GM_MP_NET && p2->GetType() == PT_LOCAL_P2) bSendUpdate = true;
			}
		}

		// Emit ball trail - rate based on framerate
		if (Props.speed > BALL_MAX_SPEED) {
			StartFireBall();
			_ballTrailEmitRate = 0.0f;
		}
		else {
			_ballTrailEmitRate -= dt;
			if (_ballTrailEmitRate <= 0.0f) {
				StartBallTrail();
				_ballTrailEmitRate = 1.0f;
			}
		}
	}

	// bounce off table
	if (Props.y < Props.radius) {
		Props.y = Props.radius;
		Props.yv = -Props.yv;
		//myGame->sMgr->Play(SFX_BALL_HIT_TABLE);
	}
	if (Props.y > TABLE_HEIGHT - Props.radius) {
		Props.y = TABLE_HEIGHT - Props.radius;
		Props.yv = -Props.yv;
		//myGame->sMgr->Play(SFX_BALL_HIT_TABLE);
	}

	// check side bounds
	if (Props.x < xMin || Props.x > xMax) { Props.xv = 0.0f; Props.yv = 0.0f; }
#endif

	// update ball spin
	if (Props.spin == BallProperties::UpSpin) 
	{
		Props.xv += 0.3f*DeltaTime;
		if (Props.xv > 1.0f) Props.xv = 1.0f;
	}
	else if (Props.spin == BallProperties::DownSpin) 
	{
		Props.xv -= 0.3f*DeltaTime;
		if (Props.xv < -1.0f) Props.xv = -1.0f;
	}

	// update ball position
	Props.x += Props.xv * Props.speed * DeltaTime;
	Props.y += Props.yv * Props.speed * DeltaTime;

	FVector NewLocation = { Props.x, Props.y, GetActorLocation().Z };
	SetActorLocation(NewLocation, true);
}

void ABall::ResetPosition(float bx, float by)
{
	Props.x = bx;
	Props.y = by;
	Props.xv = 0.0f;
	Props.yv = 0.0f;
	Props.speed = 0.0f;
	Props.spin = BallProperties::NoSpin;
}

void ABall::OnBallHitSomething(AActor* OverlapedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s hit %s"), *OverlapedActor->GetName(), *OtherActor->GetName())

	auto Player = Cast<APlayerLocal>(OtherActor);
	if (Player)
	{
		// We hit a player
		FVector Dir = Player->GetProps().LastMoveDelta.GetSafeNormal();
		Props.xv = Dir.X;
		Props.yv = Dir.Y;
		Props.speed = Player->GetProps().LastMoveDelta.Size();
		if (Props.xv > 0) { Props.spin = BallProperties::DownSpin; }
		if (Props.xv < 0) { Props.spin = BallProperties::UpSpin; }

		GameInstance->PlayerLocal->SetStatus(PlayerProperties::Playing);
	}
	else
	{
		// We hit a wall
		Props.xv = -Props.xv;
	}
}


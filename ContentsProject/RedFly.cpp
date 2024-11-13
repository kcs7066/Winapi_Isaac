#include "PreCompile.h"
#include "RedFly.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"


ARedFly::ARedFly()
{
	SetActorLocation({ 200, 0 });

	{
		RedFlyRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RedFlyRenderer->SetComponentScale({ 100, 100 });
		RedFlyRenderer->CreateAnimation("Move_RedFly", "Monster_Fly.png", 10, 11, 0.1f);
		RedFlyRenderer->ChangeAnimation("Move_RedFly");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 30, 30 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	DebugOn();
}

ARedFly::~ARedFly()
{
}

void ARedFly::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(RedFlyState::Idle, std::bind(&ARedFly::Idle, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(RedFlyState::Move, std::bind(&ARedFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.ChangeState(RedFlyState::Move);
}

void ARedFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	if (true == DeathCheck())
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		Destroy();
	}

}



void ARedFly::Idle(float _DeltaTime)
{
	//if ()
	{
		//FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}




void ARedFly::Move(float _DeltaTime)
{

	Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
	Dir.Normalize();

	FVector2D NewLocation = GetActorLocation() += Dir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 340.0f ||
		PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -340.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 170.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -170.0f
		)
	{

	}

	else
	{
		AddActorLocation(Dir * _DeltaTime * Speed);
	}




}
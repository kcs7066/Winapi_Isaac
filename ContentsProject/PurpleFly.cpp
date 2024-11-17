#include "PreCompile.h"
#include "PurpleFly.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"


APurpleFly::APurpleFly()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		MonsterRenderer->SetComponentScale({ 100, 100 });
		MonsterRenderer->CreateAnimation("Move_PurpleFly", "Monster_Fly.png", 12,13, 0.1f);
		MonsterRenderer->CreateAnimation("Die_PurpleFly", "BloodPoof.png", 0, 10, 0.1f);

		MonsterRenderer->ChangeAnimation("Move_PurpleFly");

	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50, 70 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

	SetHp(5.0f);
}

APurpleFly::~APurpleFly()
{
}

void APurpleFly::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(PurpleFlyState::Move, std::bind(&APurpleFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(PurpleFlyState::Die, std::bind(&APurpleFly::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_PurpleFly");
		}
	);

	FSM.ChangeState(PurpleFlyState::Move);
}

void APurpleFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void APurpleFly::Move(float _DeltaTime)
{


	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		FSM.ChangeState(PurpleFlyState::Die);
	}


	FVector2D NewLocation = GetActorLocation() += Dir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 338.0f ||
		PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -338.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 182.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -182.0f
		)
	{

	}

	else
	{
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

}

void APurpleFly::Die(float _DeltaTime)
{
	DeathValue = true;
	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
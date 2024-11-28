#include "PreCompile.h"
#include "RedFly.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "PlayGameMode.h"

ARedFly::ARedFly()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 150, 150 });
	MonsterRenderer->SetComponentLocation({ 0,-40 });
	MonsterRenderer->CreateAnimation("Move_RedFly", "Monster_Fly.png", 10, 11, 0.1f);
	MonsterRenderer->CreateAnimation("Die_RedFly", "BloodPoof.png", 0, 10, 0.1f);

	MonsterRenderer->ChangeAnimation("Move_RedFly");

	ShadowRenderer->SetSpriteScale(0.3f);

	CollisionComponent->SetComponentScale({ 55, 55 });

	DebugOn();
	SetHp(5.0f);
}

ARedFly::~ARedFly()
{
}

void ARedFly::BeginPlay()
{
	Super::BeginPlay();


	FSM.CreateState(RedFlyState::Move, std::bind(&ARedFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(RedFlyState::Die, std::bind(&ARedFly::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_RedFly");
		}
	);
	SwarmPlayer = UEngineSound::Play("insect swarm.wav");
	SwarmPlayer.Loop(65535);
	FSM.ChangeState(RedFlyState::Move);
}

void ARedFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}


void ARedFly::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		DieStart();
	}

	Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
	Dir.Normalize();

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

void ARedFly::DieStart()
{
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->CurRoom->MonsterNumber--;
	DelayTime = 0.0f;
	CollisionComponent->SetActive(false);
	ShadowRenderer->SetSpriteScale(0.0f);

	int RandomValue = Random.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		break;
	case 2:
		EffectPlayer = UEngineSound::Play("death burst small 2.wav");
		break;
	default:
		EffectPlayer = UEngineSound::Play("death burst small 3.wav");
		break;
	}
	SwarmPlayer.Off();
	FSM.ChangeState(RedFlyState::Die);
}

void ARedFly::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
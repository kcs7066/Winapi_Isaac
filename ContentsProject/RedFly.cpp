#include "PreCompile.h"
#include "RedFly.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

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
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst small.wav");
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
	CollisionComponent->SetActive(false);
	ShadowRenderer->SetSpriteScale(0.0f);

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
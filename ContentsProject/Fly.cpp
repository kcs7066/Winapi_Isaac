#include "PreCompile.h"
#include "Fly.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>


AFly::AFly()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 150, 150 });
	MonsterRenderer->SetComponentLocation({ 0,-40 });
	MonsterRenderer->CreateAnimation("Move_Fly", "Monster_Fly.png", 0, 1, 0.1f);
	MonsterRenderer->ChangeAnimation("Move_Fly");
	MonsterRenderer->CreateAnimation("Die_Fly", "BloodPoof.png", 0, 10, 0.1f);
	
	ShadowRenderer->SetSpriteScale(0.3f);

	CollisionComponent->SetComponentScale({ 55, 55 });

	DebugOn();

	SetHp(3.0f);
}

AFly::~AFly()
{
}

void AFly::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(FlyState::Move, std::bind(&AFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(FlyState::Die, std::bind(&AFly::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Fly");
		}
	);

	FSM.ChangeState(FlyState::Move);
}

void AFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AFly::Move(float _DeltaTime)
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

	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

	RandomDir.Normalize();


	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
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
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}


	

}


void AFly::DieStart()
{
	CollisionComponent->SetActive(false);
	FSM.ChangeState(FlyState::Die);
}

void AFly::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
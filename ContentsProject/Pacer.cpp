#include "PreCompile.h"
#include "Pacer.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"


APacer::APacer()
	: AMonster()
{


	MonsterRenderer->SetComponentScale({ 140, 140 });
	MonsterRenderer->SetComponentLocation({ 0,-10 });

	MonsterRenderer->CreateAnimation("Run_RightBody", "Monster_Pacer.png", 10, 19, 0.1f);
	MonsterRenderer->CreateAnimation("Run_DownBody", "Monster_Pacer.png", 0, 9, 0.1f);
	MonsterRenderer->CreateAnimation("Run_LeftBody", "Monster_Pacer_Left.png", 0, 9, 0.1f);
	MonsterRenderer->CreateAnimation("Die_Pacer", "BloodPoof.png", 0, 10, 0.1f);


	MonsterRenderer->ChangeAnimation("Run_DownBody");



	ShadowRenderer->SetSpriteScale(0.25f);

	CollisionComponent->SetComponentScale({ 40, 40 });

	DebugOn();

	SetHp(10.0f);
}

APacer::~APacer()
{
}

void APacer::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(PacerState::Move, std::bind(&APacer::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(PacerState::Die, std::bind(&APacer::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Pacer");
		}
	);

	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

	RandomDir.Normalize();

	FSM.ChangeState(PacerState::Move);
}

void APacer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void APacer::Move(float _DeltaTime)
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


	if (0.7f < RandomDir.X)
	{
		MonsterRenderer->ChangeAnimation("Run_RightBody");
	}

	else if (-0.7f > RandomDir.X)
	{
		MonsterRenderer->ChangeAnimation("Run_LeftBody");
	}

	else
	{
		MonsterRenderer->ChangeAnimation("Run_DownBody");
	}

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
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure, RandomDir * _DeltaTime * Speed);

		if (nullptr != StructureResult)
		{

		}
		else
		{
			AddActorLocation(RandomDir * _DeltaTime * Speed);
		}
	}


	if (0.5f < DelayTime)
	{
		RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

		RandomDir.Normalize();
		DelayTime = 0.0f;
	}


}


void APacer::DieStart()
{
	CollisionComponent->SetActive(false);
	MonsterRenderer->SetComponentScale(FVector2D::ZERO);
	FSM.ChangeState(PacerState::Die);
}

void APacer::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{

		Destroy();
	}
}
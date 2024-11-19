#include "PreCompile.h"
#include "LevelTwoSpiderSmall.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "PlayGameMode.h"
#include "Spider.h"


ALevelTwoSpiderSmall::ALevelTwoSpiderSmall()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		MonsterRenderer->SetComponentScale({ 100, 65	 });
		MonsterRenderer->SetComponentLocation({ 0, -20 });


		MonsterRenderer->CreateAnimation("Idle_LevelTwoSpiderSmall", "Monster_LevelTwoSpiderSmall.png", 4, 4, 0.1f);
		MonsterRenderer->CreateAnimation("Move_LevelTwoSpiderSmall", "Monster_LevelTwoSpiderSmall.png", 0, 3, 0.1f);
		MonsterRenderer->CreateAnimation("Attack_LevelTwoSpiderSmall", "Monster_LevelTwoSpiderSmall.png", 
			{5, 6, 7, 6, 5}, { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
		MonsterRenderer->CreateAnimation("Die_LevelTwoSpiderSmall", "BloodPoof.png", 0, 10, 0.1f);



		MonsterRenderer->ChangeAnimation("Idle_LevelTwoSpiderSmall");
	}

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetSpriteScale(0.25f);



	CollisionComponent->SetComponentScale({ 80, 50 });

	DebugOn();

	SetHp(13.0f);
}

ALevelTwoSpiderSmall::~ALevelTwoSpiderSmall()
{
}

void ALevelTwoSpiderSmall::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(LevelTwoSpiderSmallState::Idle, std::bind(&ALevelTwoSpiderSmall::Idle, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Idle_LevelTwoSpiderSmall");
		}
	);

	FSM.CreateState(LevelTwoSpiderSmallState::Move, std::bind(&ALevelTwoSpiderSmall::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_LevelTwoSpiderSmall");
		}
	);


	FSM.CreateState(LevelTwoSpiderSmallState::Jump, std::bind(&ALevelTwoSpiderSmall::Jump, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_LevelTwoSpiderSmall");
		}
	);

	FSM.CreateState(LevelTwoSpiderSmallState::Die, std::bind(&ALevelTwoSpiderSmall::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_LevelTwoSpiderSmall");
		}
	);


	FSM.ChangeState(LevelTwoSpiderSmallState::Idle);
}

void ALevelTwoSpiderSmall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FSM.Update(_DeltaTime);

}

void ALevelTwoSpiderSmall::Idle(float _DeltaTime)
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

	if (DelayTime > 1.0f)
	{
		int RandomValue = Random.RandomInt(1, 2);

		switch (RandomValue)
		{
		case 1:
			FSM.ChangeState(LevelTwoSpiderSmallState::Move);
			DelayTime = 0.0f;
			break;	
		case 2:
			FSM.ChangeState(LevelTwoSpiderSmallState::Jump);
			DelayTime = 0.0f;
			break;
		default:
			break;
		}


	}
}


void ALevelTwoSpiderSmall::Jump(float _DeltaTime)
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

	if (DelayTime < 0.25f)
	{
		MonsterRenderer->SetComponentLocation({ 0,-50 });
		ShadowRenderer->SetSpriteScale(0.15f);

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
	else
	{
		MonsterRenderer->SetComponentLocation({ 0,-20 });
		ShadowRenderer->SetSpriteScale(0.25f);
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

	if (DelayTime > 0.5f)
	{
		FSM.ChangeState(LevelTwoSpiderSmallState::Idle);
		DelayTime = 0.0f;
	}
}

void ALevelTwoSpiderSmall::Move(float _DeltaTime)
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

	Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation() ;
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

	if (DelayTime > 0.5f)
	{

		FSM.ChangeState(LevelTwoSpiderSmallState::Idle);
		DelayTime = 0.0f;
	}

}

void ALevelTwoSpiderSmall::DieStart()
{
	CollisionComponent->SetActive(false);
	FSM.ChangeState(LevelTwoSpiderSmallState::Die);
}

void ALevelTwoSpiderSmall::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
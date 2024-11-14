#include "PreCompile.h"
#include "Dip.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "PlayGameMode.h"


ADip::ADip()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetComponentScale({ 100, 100 });

		MonsterRenderer->CreateAnimation("Idle_Dip_Left", "Monster_Dip_Left.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Idle_Dip_Right", "Monster_Dip_Right.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Dip_Left", "Monster_Dip_Left.png", 0, 4, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Dip_Right", "Monster_Dip_Right.png", 0, 4, 0.1f);
		MonsterRenderer->CreateAnimation("Die_Dip", "BloodPoof.png", 0, 10, 0.1f);


		MonsterRenderer->ChangeAnimation("Idle_Dip_Right");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50, 60 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

	SetHp(3.0f);
}

ADip::~ADip()
{
}

void ADip::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(DipState::IdleRight, std::bind(&ADip::Idle, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Idle_Dip_Right");
		}
	);

	FSM.CreateState(DipState::IdleLeft, std::bind(&ADip::Idle, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Idle_Dip_Left");
		}
	);

	FSM.CreateState(DipState::MoveLeft, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Dip_Left");
		}
	);

	FSM.CreateState(DipState::MoveRight, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Dip_Right");
		}
	);

	FSM.CreateState(DipState::Die, std::bind(&ADip::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Dip");
		}
	);

	FSM.ChangeState(DipState::IdleRight);

	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

	RandomDir.Normalize();
}

void ADip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
    FSM.Update(_DeltaTime);
}

void ADip::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(DipState::Die);
	}

	if (DelayTime > 1.6f)
	{
		FSM.ChangeState(DipState::MoveRight);
		DelayTime = 0.0f;
	}
}

void ADip::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(DipState::Die);
	}

	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 338.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -338.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 182.0f)
	{
		RandomDir.Y *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if(PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -182.0f)
	{
		RandomDir.Y *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else
	{
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}
	
	if (DelayTime > 1.0f)
	{
		RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

		RandomDir.Normalize();

		FSM.ChangeState(DipState::IdleRight);
		DelayTime = 0.0f;
	}

}

void ADip::Die(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
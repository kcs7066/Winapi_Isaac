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
		DipRenderer = CreateDefaultSubObject<USpriteRenderer>();
		DipRenderer->SetComponentScale({ 100, 100 });

		DipRenderer->CreateAnimation("Idle_Dip_Left", "Monster_Dip_Left.png", 0, 1, 0.1f);
		DipRenderer->CreateAnimation("Idle_Dip_Right", "Monster_Dip_Right.png", 0, 1, 0.1f);
		DipRenderer->CreateAnimation("Move_Dip_Left", "Monster_Dip_Left.png", 0, 4, 0.1f);
		DipRenderer->CreateAnimation("Move_Dip_Right", "Monster_Dip_Right.png", 0, 4, 0.1f);


		DipRenderer->ChangeAnimation("Idle_Dip_Right");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50, 60 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();


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
			DipRenderer->ChangeAnimation("Idle_Dip_Right");
		}
	);

	FSM.CreateState(DipState::IdleLeft, std::bind(&ADip::Idle, this, std::placeholders::_1),
		[this]()
		{
			DipRenderer->ChangeAnimation("Idle_Dip_Left");
		}
	);

	FSM.CreateState(DipState::MoveLeft, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			DipRenderer->ChangeAnimation("Move_Dip_Left");
		}
	);

	FSM.CreateState(DipState::MoveRight, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			DipRenderer->ChangeAnimation("Move_Dip_Right");
		}
	);

	FSM.ChangeState(DipState::IdleRight);

	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

	RandomDir.Normalize();
}

void ADip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DelayTime += _DeltaTime;

	FSM.Update(_DeltaTime);

	if (true == DeathCheck())
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		Destroy();
	}
}

void ADip::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.6f)
	{
		FSM.ChangeState(DipState::MoveRight);
		DelayTime = 0.0f;
	}
}

void ADip::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 340.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -340.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 170.0f)
	{
		RandomDir.Y *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if(PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -170.0f)
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

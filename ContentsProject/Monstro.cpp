#include "PreCompile.h"
#include "Monstro.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "MonsterTear.h"
#include "PlayGameMode.h"
#include "TrapDoor.h"

AMonstro::AMonstro()
{
	SetActorLocation({ 200, 0 });

	{
		MonstroRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonstroRenderer->SetComponentScale({ 300, 300 });

		MonstroRenderer->CreateAnimation("Idle_Monstro", "Boss_Monstro.png", 0, 0, 0.1f);
		MonstroRenderer->CreateAnimation("Move_Monstro", "Boss_Monstro.png", 1, 2, 0.5f);
		MonstroRenderer->CreateAnimation("Attack_Monstro", "Boss_Monstro.png", { 3,4 }, { 0.5f,0.5f });
		MonstroRenderer->CreateAnimation("Jump_Monstro", "Boss_Monstro.png", { 5,9,6,7 }, { 0.3f,1.5f,0.3f,0.5f });

		MonstroRenderer->ChangeAnimation("Idle_Monstro");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 160, 120 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

}

AMonstro::~AMonstro()
{
}

void AMonstro::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(MonstroState::Idle, std::bind(&AMonstro::Idle, this, std::placeholders::_1),
		[this]()
		{
			MonstroRenderer->ChangeAnimation("Idle_Monstro");
		}
	);

	FSM.CreateState(MonstroState::Move, std::bind(&AMonstro::Move, this, std::placeholders::_1),
		[this]()
		{
			MonstroRenderer->ChangeAnimation("Move_Monstro");
		}
	);

	FSM.CreateState(MonstroState::Attack, std::bind(&AMonstro::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonstroRenderer->ChangeAnimation("Attack_Monstro");
		}
	);

	FSM.CreateState(MonstroState::Jump, std::bind(&AMonstro::Jump, this, std::placeholders::_1),
		[this]()
		{
			MonstroRenderer->ChangeAnimation("Jump_Monstro");
		}
	);

	FSM.ChangeState(MonstroState::Idle);
}

void AMonstro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	BulletCoolTime -= _DeltaTime;
	if (true == DeathCheck())
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		Destroy();
	}
}



void AMonstro::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 2.0f)
	{
		int RandomValue = Random.RandomInt(1,3);

		switch (RandomValue)
		{
		case 1:
			FSM.ChangeState(MonstroState::Move);
			break;
		case 2:
			FSM.ChangeState(MonstroState::Attack);
			break;
		case 3:
			FSM.ChangeState(MonstroState::Jump);
			break;

		default:
			break;
		}

		DelayTime = 0.0f;
	}
}

void AMonstro::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (DelayTime < 0.5f)
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

	if (DelayTime > 1.0f)
	{
		FSM.ChangeState(MonstroState::Idle);
		DelayTime = 0.0f;
	}
}

void AMonstro::Attack(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 0.5f)
	{
		if (BulletCoolTime < 0.0f)
		{
			AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
			NewTear->SetActorLocation(GetActorLocation());
			NewTear->Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
			BulletCoolTime = 1.5f;
		}

		if (DelayTime > 1.0f)
		{
			FSM.ChangeState(MonstroState::Idle);
			DelayTime = 0.0f;
		}
	}
}

void AMonstro::Jump(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (DelayTime > 1.5f)
	{

		if (DelayTime < 1.6f)
		{
			SetActorLocation({ GetWorld()->GetPawn()->GetActorLocation() });
		}
	}

		if (DelayTime > 2.6f)
		{
			FSM.ChangeState(MonstroState::Idle);
			DelayTime = 0.0f;
		}
	



}

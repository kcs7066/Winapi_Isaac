#include "PreCompile.h"
#include "Monstro.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "MonsterTear.h"
#include "PlayGameMode.h"
#include "TrapDoor.h"

AMonstro::AMonstro()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 250, 250 });
	MonsterRenderer->SetComponentLocation({ 0,-40 });

	MonsterRenderer->CreateAnimation("Idle_Monstro", "Boss_Monstro.png", 0, 0, 0.1f);
	MonsterRenderer->CreateAnimation("Move_Monstro", "Boss_Monstro.png", 1, 2, 0.5f);
	MonsterRenderer->CreateAnimation("Attack_Monstro", "Boss_Monstro.png", { 3,4 }, { 0.5f,0.5f });
	MonsterRenderer->CreateAnimation("Jump_Monstro", "Boss_Monstro.png", { 5,9,6,7 }, { 0.3f,1.5f,0.3f,0.5f });
	MonsterRenderer->CreateAnimation("Die_Monstro", "BloodPoof.png", 0, 10, 0.1f);

	MonsterRenderer->ChangeAnimation("Idle_Monstro");

	ShadowRenderer->SetSpriteScale(1.0f);

	CollisionComponent->SetComponentScale({ 100, 100 });
	CollisionComponent->SetComponentLocation({ 0, -10 });

	DebugOn();

	SetHp(250.0f);
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
			MonsterRenderer->ChangeAnimation("Idle_Monstro");
			CollisionComponent->SetActive(true);
		}
	);

	FSM.CreateState(MonstroState::Move, std::bind(&AMonstro::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Monstro");
		}
	);

	FSM.CreateState(MonstroState::Attack, std::bind(&AMonstro::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_Monstro");
		}
	);

	FSM.CreateState(MonstroState::Jump, std::bind(&AMonstro::Jump, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Jump_Monstro");
			CollisionComponent->SetActive(false);
		}
	);

	FSM.CreateState(MonstroState::Die, std::bind(&AMonstro::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Monstro");
		}
	);

	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("basic boss fight.ogg");
	FSM.ChangeState(MonstroState::Idle);
}

void AMonstro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	TearCoolTime -= _DeltaTime;
}



void AMonstro::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		DieStart();
	}

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

	if (this->Hp <= 0.0f)
	{
		DieStart();
	}

	if (DelayTime < 0.5f)
	{
		MonsterRenderer->SetComponentLocation({ 0,-150 });
		ShadowRenderer->SetSpriteScale(0.8f);

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
		MonsterRenderer->SetComponentLocation({ 0,-40 });
		ShadowRenderer->SetSpriteScale(1.0f);
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

	if (this->Hp <= 0.0f)
	{
		DieStart();
	}

	if (DelayTime > 0.5f)
	{
		if (TearCoolTime < 0.0f)
		{
			AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
			NewTear->TearSpeed = 500.0f;
			NewTear->SetActorLocation(GetActorLocation());
			NewTear->Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
			NewTear->Dir.Normalize();
			TearCoolTime = 1.5f;
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

	ShadowRenderer->SetSpriteScale(0.4f);



	if (DelayTime > 0.3f)
	{
		if (DelayTime > 1.0f)
		{

		}
		else
		{
		
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

	}

	if (DelayTime > 1.8f)
	{
		ShadowRenderer->SetSpriteScale(1.0f);
		if (TearCoolTime < 0.0f)
		{
			AMonsterTear* NewTear1 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear2 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear3 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear4 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear5 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear6 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear7 = GetWorld()->SpawnActor<AMonsterTear>();
			AMonsterTear* NewTear8 = GetWorld()->SpawnActor<AMonsterTear>();
			NewTear1->TearSpeed = 500.0f;
			NewTear2->TearSpeed = 500.0f;
			NewTear3->TearSpeed = 500.0f;
			NewTear4->TearSpeed = 500.0f;
			NewTear5->TearSpeed = 500.0f;
			NewTear6->TearSpeed = 500.0f;
			NewTear7->TearSpeed = 500.0f;
			NewTear8->TearSpeed = 500.0f;
			NewTear1->SetActorLocation(GetActorLocation());
			NewTear2->SetActorLocation(GetActorLocation());
			NewTear3->SetActorLocation(GetActorLocation());
			NewTear4->SetActorLocation(GetActorLocation());
			NewTear5->SetActorLocation(GetActorLocation());
			NewTear6->SetActorLocation(GetActorLocation());
			NewTear7->SetActorLocation(GetActorLocation());
			NewTear8->SetActorLocation(GetActorLocation());
			NewTear1->Dir = FVector2D::UP;
			NewTear2->Dir = FVector2D::RIGHT;
			NewTear3->Dir = FVector2D::DOWN;
			NewTear4->Dir = FVector2D::LEFT;
			NewTear5->Dir = FVector2D::UP + FVector2D::RIGHT;
			NewTear6->Dir = FVector2D::UP + FVector2D::LEFT;
			NewTear7->Dir = FVector2D::DOWN + FVector2D::RIGHT;
			NewTear8->Dir = FVector2D::DOWN + FVector2D::LEFT;
			NewTear5->Dir.Normalize();
			NewTear6->Dir.Normalize();
			NewTear7->Dir.Normalize();
			NewTear8->Dir.Normalize();
			TearCoolTime = 1.5f;
		}
		if (DelayTime > 2.1f)
		{
			MonsterRenderer->SetComponentLocation({ 0,0 });

		}
	}
	
		if (DelayTime > 2.6f)
		{
			MonsterRenderer->SetComponentLocation({ 0,-40 });
			FSM.ChangeState(MonstroState::Idle);
			DelayTime = 0.0f;
		}
	



}

void AMonstro::DieStart()
{
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->CurRoom->MonsterNumber--;
	ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
	NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
	DelayTime = 0.0f;
	EffectPlayer = UEngineSound::Play("death burst large.wav");
	CollisionComponent->SetActive(false);
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("secret to everyone.ogg");
	ShadowRenderer->SetSpriteScale(0.0f);


	int RandomValue = Random.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		break;
	default:
		EffectPlayer = UEngineSound::Play("death burst large 2.wav");
		break;
	}
	FSM.ChangeState(MonstroState::Die);
}

void AMonstro::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
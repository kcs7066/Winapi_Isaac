#include "PreCompile.h"
#include "Monstro.h"

#include <EnginePlatform/EngineInput.h>
#include "MonsterTear.h"
#include "PlayGameMode.h"
#include "TrapDoor.h"


AMonstro::AMonstro()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		MonsterRenderer->SetComponentScale({ 250, 250 });
		MonsterRenderer->SetComponentLocation({ 0,-40 });

		MonsterRenderer->CreateAnimation("Idle_Monstro", "Boss_Monstro.png", 0, 0, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Monstro", "Boss_Monstro.png", 1, 2, 0.5f);
		MonsterRenderer->CreateAnimation("Attack_Monstro", "Boss_Monstro.png", { 3,4 }, { 0.5f,0.5f });
		MonsterRenderer->CreateAnimation("Jump_Monstro", "Boss_Monstro.png", { 5,9,6,7 }, { 0.3f,1.5f,0.3f,0.5f });
		MonsterRenderer->CreateAnimation("Die_Monstro", "BloodPoof.png", 0, 10, 0.1f);

		MonsterRenderer->ChangeAnimation("Idle_Monstro");
	}

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetSpriteScale(1.0f);


	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 100, 100 });
	CollisionComponent->SetComponentLocation({ 0, -10 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

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

		}
	);

	FSM.CreateState(MonstroState::DieStay, std::bind(&AMonstro::DieStay, this, std::placeholders::_1),
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
	BulletCoolTime -= _DeltaTime;
}



void AMonstro::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(MonstroState::Die);
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
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(MonstroState::Die);
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
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(MonstroState::Die);

	}

	if (DelayTime > 0.5f)
	{
		if (BulletCoolTime < 0.0f)
		{
			AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
			NewTear->BulletSpeed = 1.0f;
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

	ShadowRenderer->SetSpriteScale(0.4f);



	if (DelayTime > 0.3f)
	{
		if (DelayTime > 1.6f)
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

		if (DelayTime > 2.1f)
		{
			MonsterRenderer->SetComponentLocation({ 0,-40 });

		}
	}
	
		if (DelayTime > 2.6f)
		{
			FSM.ChangeState(MonstroState::Idle);
			DelayTime = 0.0f;
		}
	



}

void AMonstro::Die(float _DeltaTime)
{
	DeathValue = true;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("secret to everyone.ogg");
	FSM.ChangeState(MonstroState::DieStay);
}

void AMonstro::DieStay(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
#include "PreCompile.h"
#include "Pooter.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "PlayGameMode.h"
#include "MonsterTear.h"
#include "ContentsEnum.h"


APooter::APooter()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 70, 70 });
	MonsterRenderer->SetComponentLocation({ 0,-40 });
	MonsterRenderer->CreateAnimation("Move_Pooter", "Monster_Pooter.png", 0, 1, 0.1f);
	MonsterRenderer->ChangeAnimation("Move_Pooter");
	MonsterRenderer->CreateAnimation("Attack_Pooter", "Monster_Pooter.png", 2, 15, 0.05f);
	MonsterRenderer->CreateAnimation("Die_Pooter", "BloodPoof.png", 0, 10, 0.1f);

	ShadowRenderer->SetSpriteScale(0.2f);

	CollisionComponent->SetComponentScale({ 50, 50 });

	AttackRadius = CreateDefaultSubObject<U2DCollision>();
	AttackRadius->SetComponentScale({ 400, 400 });
	AttackRadius->SetCollisionGroup(ECollisionGroup::Radius);
	AttackRadius->SetCollisionType(ECollisionType::CirCle);


	DebugOn();

	SetHp(8.0f);
}

APooter::~APooter()
{
}

void APooter::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(PooterState::Move, std::bind(&APooter::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Pooter");
		}
	);

	FSM.CreateState(PooterState::Attack, std::bind(&APooter::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_Pooter");
		}
	);

	FSM.CreateState(PooterState::Die, std::bind(&APooter::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Pooter");
		}
	);

	FSM.ChangeState(PooterState::Move);
}

void APooter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	TearCoolTime -= _DeltaTime;
}

void APooter::Move(float _DeltaTime)
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

	FVector2D PlayerDir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
	PlayerDir.Normalize();

	PlayerDir = PlayerDir / 10;

	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };
	RandomDir.Normalize();

	FVector2D Dir = RandomDir + PlayerDir;
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

	AActor* Result = AttackRadius->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		if (0.0f >= TearCoolTime)
		{
			DelayTime = 0.0f;
			FSM.ChangeState(PooterState::Attack);
		}
	}


}

void APooter::AttackStart()
{
	AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
	NewTear->SetActorLocation(GetActorLocation());
	NewTear->Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
	NewTear->Dir.Normalize();
	NewTear->Dir = NewTear->Dir * TearSpeed;
	TearCoolTime = 1.5f;
}

void APooter::Attack(float _DeltaTime)
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

	if (0.35f <= DelayTime)
	{
		if (0.0f >= TearCoolTime)
		{
			AttackStart();
		}
	}

	if (0.65f <= DelayTime)
	{
		DelayTime = 0.0f;
		FSM.ChangeState(PooterState::Move);
	}
}

void APooter::DieStart()
{
	CollisionComponent->SetActive(false);
	ShadowRenderer->SetSpriteScale(0.0f);

	FSM.ChangeState(PooterState::Die);
}

void APooter::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
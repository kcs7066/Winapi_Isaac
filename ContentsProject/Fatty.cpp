#include "PreCompile.h"
#include "Fatty.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "PlayGameMode.h"
#include "ContentsEnum.h"
#include "Pacer.h"

AFatty::AFatty()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 140, 140 });
	MonsterRenderer->SetComponentLocation({ 0,-65 });
	MonsterRenderer->CreateAnimation("Move_FattyHead", "Monster_Fatty.png", 0, 5, 0.1f);
	MonsterRenderer->CreateAnimation("Attack_FattyHead", "Monster_Fatty.png", { 6,7,8 }, { 0.2f,0.6f,0.2f });
	MonsterRenderer->ChangeAnimation("Move_FattyHead");
	MonsterRenderer->CreateAnimation("Die_Fatty", "BloodPoof.png", 0, 10, 0.1f);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BodyRenderer->SetOrder(ERenderOrder::MONSTERBACK);
	BodyRenderer->SetComponentScale({ 140, 140 });
	BodyRenderer->SetComponentLocation({ 0,-25 });

	BodyRenderer->CreateAnimation("Move_RightBody", "Monster_Fatty.png", 9, 20, 0.1f);
	BodyRenderer->CreateAnimation("Move_DownBody", "Monster_Fatty.png", 21, 32, 0.1f);
	BodyRenderer->CreateAnimation("Move_LeftBody", "Monster_Fatty_Left.png", 0, 11, 0.1f);
	BodyRenderer->CreateAnimation("Attack_Body", "Monster_Fatty.png", { 26,25,24,25,26 }, { 0.2f,0.2f,0.2f,0.2f,0.2f });
	BodyRenderer->ChangeAnimation("Move_DownBody");

	ShadowRenderer->SetSpriteScale(0.3f);

	NewPoofRenderer = CreateDefaultSubObject<USpriteRenderer>();
	NewPoofRenderer->SetOrder(ERenderOrder::MONSTERBACK);
	NewPoofRenderer->SetComponentLocation({ 0,-50 });
	NewPoofRenderer->SetComponentScale({ 0,0 });
	NewPoofRenderer->CreateAnimation("Poof", "Effect_Poof.png", 0, 14, 0.05f);
	NewPoofRenderer->ChangeAnimation("Poof");

	CollisionComponent->SetComponentScale({ 40, 40 });

	DebugOn();

	SetHp(20.0f);
}

AFatty::~AFatty()
{
}

void AFatty::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(FattyState::Move, std::bind(&AFatty::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_FattyHead");
			NewPoofRenderer->SetComponentScale({ 0,0 });
		}
	);

	FSM.CreateState(FattyState::Attack, std::bind(&AFatty::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_FattyHead");
			BodyRenderer->ChangeAnimation("Attack_Body");
			NewPoofRenderer->SetComponentScale({ 200,200 });
		}
	);

	FSM.CreateState(FattyState::Die, std::bind(&AFatty::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Fatty");
			NewPoofRenderer->SetComponentScale({ 0,0 });
		}
	);

	FSM.ChangeState(FattyState::Move);
}

void AFatty::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AFatty::Move(float _DeltaTime)
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

	if (0.7f < Dir.X)
	{
		BodyRenderer->ChangeAnimation("Move_RightBody");
	}

	else if (-0.7f > Dir.X)
	{
		BodyRenderer->ChangeAnimation("Move_LeftBody");
	}

	else
	{
		BodyRenderer->ChangeAnimation("Move_DownBody");
	}

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
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure, Dir * _DeltaTime * Speed);

		if (nullptr != StructureResult)
		{

		}
		else
		{
			AddActorLocation(Dir * _DeltaTime * Speed);
		}
	}

	if (DelayTime > 5.0f)
	{
		FSM.ChangeState(FattyState::Attack);
		DelayTime = 0.0f;
	}

}

void AFatty::Attack(float _DeltaTime)
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

		FSM.ChangeState(FattyState::Move);
		NewPoofRenderer->SetComponentScale({ 0,0 });
		DelayTime = 0.0f;
	}
}


void AFatty::DieStart()
{
	CollisionComponent->SetActive(false);
	BodyRenderer->SetComponentScale(FVector2D::ZERO);
	ShadowRenderer->SetSpriteScale(0.0f);

	FSM.ChangeState(FattyState::Die);
}

void AFatty::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{

		Destroy();
	}
}
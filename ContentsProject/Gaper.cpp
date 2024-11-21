#include "PreCompile.h"
#include "Gaper.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"
#include "Pacer.h"

AGaper::AGaper()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 70, 70 });
	MonsterRenderer->SetComponentLocation({ 0,-40 });
	MonsterRenderer->CreateAnimation("Head_Gaper", "Monster_Gaper.png", 1, 1, 0.1f);
	MonsterRenderer->ChangeAnimation("Head_Gaper");
	MonsterRenderer->CreateAnimation("Die_Gaper", "BloodPoof.png", 0, 10, 0.1f);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BodyRenderer->SetOrder(ERenderOrder::MONSTERBACK);
	BodyRenderer->SetComponentScale({ 70, 70 });
	BodyRenderer->SetComponentLocation({ 0,-10 });
	
	BodyRenderer->CreateAnimation("Run_RightBody", "Body.png", 10, 19, 0.1f);
	BodyRenderer->CreateAnimation("Run_DownBody", "Body.png", 20, 29, 0.1f);
	BodyRenderer->CreateAnimation("Run_LeftBody", "Body.png", 0, 9, 0.1f);

	BodyRenderer->ChangeAnimation("Run_DownBody");

	ShadowRenderer->SetSpriteScale(0.3f);

	CollisionComponent->SetComponentScale({ 40, 40 });

	DebugOn();

	SetHp(10.0f);
}

AGaper::~AGaper()
{
}

void AGaper::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(GaperState::Move, std::bind(&AGaper::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(GaperState::Die, std::bind(&AGaper::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Gaper");
		}
	);

	FSM.ChangeState(GaperState::Move);
}

void AGaper::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AGaper::Move(float _DeltaTime)
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
		BodyRenderer->ChangeAnimation("Run_RightBody");
	}

	else if (-0.7f > Dir.X)
	{
		BodyRenderer->ChangeAnimation("Run_LeftBody");
	}

	else
	{
		BodyRenderer->ChangeAnimation("Run_DownBody");
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




}


void AGaper::DieStart()
{
	CollisionComponent->SetActive(false);
	BodyRenderer->SetComponentScale(FVector2D::ZERO);
	FSM.ChangeState(GaperState::Die);
	int RandomValue = Random.RandomInt(1, 2);
	if(1 == RandomValue)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber++;
		APacer* Monster = GetWorld()->SpawnActor<APacer>();
		Monster->SetActorLocation(GetActorLocation());
	}
	else
	{
	}
}

void AGaper::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{

		Destroy();
	}
}
#include "PreCompile.h"
#include "BabyLongLegs.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "PlayGameMode.h"
#include "Spider.h"

ABabyLongLegs::ABabyLongLegs()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetComponentScale({ 300, 300 });

		MonsterRenderer->CreateAnimation("Move_BabyLongLegs", "Monster_BabyLongLegs.png", 0, 4, 0.1f);
		MonsterRenderer->CreateAnimation("Attack_BabyLongLegs", "Monster_BabyLongLegs.png", 5, 7, 0.1f);
		MonsterRenderer->CreateAnimation("Die_BabyLongLegs", "BloodPoof.png", 0, 10, 0.1f);
		MonsterRenderer->ChangeAnimation("Move_BabyLongLegs");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 84, 100 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

	SetHp(16.0f);
}

ABabyLongLegs::~ABabyLongLegs()
{
}

void ABabyLongLegs::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(BabyLongLegsState::Move, std::bind(&ABabyLongLegs::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_BabyLongLegs");
		}
	);


	FSM.CreateState(BabyLongLegsState::Attack, std::bind(&ABabyLongLegs::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_BabyLongLegs");
		}
	);

	FSM.CreateState(BabyLongLegsState::Die, std::bind(&ABabyLongLegs::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_BabyLongLegs");
		}
	);

	FSM.ChangeState(BabyLongLegsState::Move);
}

void ABabyLongLegs::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}
	
	
	



void ABabyLongLegs::Attack(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(BabyLongLegsState::Die);
	}

	if (DelayTime > 0.3f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

		if (PlayGameMode->CurRoom->SpiderNumber < 5)
		{
			ASpider* Monster = GetWorld()->SpawnActor<ASpider>();
			Monster->SetActorLocation(GetActorLocation());
			PlayGameMode->CurRoom->SpiderNumber++;
		}
		FSM.ChangeState(BabyLongLegsState::Move);
		DelayTime = 0.0f;
	}
}

void ABabyLongLegs::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	
	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(BabyLongLegsState::Die);
	}

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(BabyLongLegsState::Die);
	}

	Dir = GetActorLocation() - GetWorld()->GetPawn()->GetActorLocation();
	Dir.Normalize();

	FVector2D NewLocation = GetActorLocation() += Dir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 290.0f ||
		PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -290.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 120.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -120.0f
		)
	{

	}

	else
	{
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

	if (DelayTime > 2.0f)
	{
		
		FSM.ChangeState(BabyLongLegsState::Attack);
		DelayTime = 0.0f;
	}

}

void ABabyLongLegs::Die(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
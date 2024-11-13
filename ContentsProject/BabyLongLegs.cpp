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
		BabyLongLegsRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BabyLongLegsRenderer->SetComponentScale({ 300, 300 });

		BabyLongLegsRenderer->CreateAnimation("Move_BabyLongLegs", "Monster_BabyLongLegs.png", 0, 4, 0.1f);
		BabyLongLegsRenderer->CreateAnimation("Attack_BabyLongLegs", "Monster_BabyLongLegs.png", 5, 7, 0.1f);

		BabyLongLegsRenderer->ChangeAnimation("Move_BabyLongLegs");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, -50 });
	CollisionComponent->SetComponentScale({ 84, 100 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

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
			BabyLongLegsRenderer->ChangeAnimation("Move_BabyLongLegs");
		}
	);


	FSM.CreateState(BabyLongLegsState::Attack, std::bind(&ABabyLongLegs::Attack, this, std::placeholders::_1),
		[this]()
		{
			BabyLongLegsRenderer->ChangeAnimation("Attack_BabyLongLegs");
		}
	);



	FSM.ChangeState(BabyLongLegsState::Move);
}

void ABabyLongLegs::Tick(float _DeltaTime)
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
	
	
	



void ABabyLongLegs::Attack(float _DeltaTime)
{
	DelayTime += _DeltaTime;

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

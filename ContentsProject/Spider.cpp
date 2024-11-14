#include "PreCompile.h"
#include "Spider.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"

ASpider::ASpider()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetComponentScale({ 100, 100 });

		MonsterRenderer->CreateAnimation("Idle_Spider", "Monster_Spider.png", 0, 0, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Spider_Right", "Monster_Spider.png", 2, 3, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Spider_Left", "Monster_Spider.png", 6, 7, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Spider_Up", "Monster_Spider.png", 4, 5, 0.1f);
		MonsterRenderer->CreateAnimation("Move_Spider_Down", "Monster_Spider.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Die_Spider", "BloodPoof.png", 0, 10, 0.1f);

		MonsterRenderer->ChangeAnimation("Idle_Spider");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 30, 15 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

	SetHp(7.0f);
}

ASpider::~ASpider()
{
}

void ASpider::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(SpiderState::Idle, std::bind(&ASpider::Idle, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Idle_Spider");
		}
	);


	FSM.CreateState(SpiderState::MoveLeft, std::bind(&ASpider::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Spider_Left");
		}
	);

	FSM.CreateState(SpiderState::MoveRight, std::bind(&ASpider::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Spider_Right");
		}
	);

	FSM.CreateState(SpiderState::Die, std::bind(&ASpider::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Spider");
		}
	);

	FSM.ChangeState(SpiderState::Idle);
}

void ASpider::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DelayTime += _DeltaTime;

	FSM.Update(_DeltaTime);
}

void ASpider::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(SpiderState::Die);
	}

	if (DelayTime > 1.0f)
	{
		FSM.ChangeState(SpiderState::MoveRight);
		DelayTime = 0.0f;
	}
}

void ASpider::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		FSM.ChangeState(SpiderState::Die);
	}

	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
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
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	if (DelayTime > 1.0f)
	{
		RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

		RandomDir.Normalize();

		FSM.ChangeState(SpiderState::Idle);
		DelayTime = 0.0f;
	}

}

void ASpider::Die(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
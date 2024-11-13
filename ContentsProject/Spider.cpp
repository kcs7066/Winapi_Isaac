#include "PreCompile.h"
#include "Spider.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"

ASpider::ASpider()
{
	SetActorLocation({ 200, 0 });

	{
		SpiderRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpiderRenderer->SetComponentScale({ 100, 100 });

		SpiderRenderer->CreateAnimation("Idle_Spider", "Monster_Spider.png", 0, 0, 0.1f);
		SpiderRenderer->CreateAnimation("Move_Spider_Right", "Monster_Spider.png", 2, 3, 0.1f);
		SpiderRenderer->CreateAnimation("Move_Spider_Left", "Monster_Spider.png", 6, 7, 0.1f);
		SpiderRenderer->CreateAnimation("Move_Spider_Up", "Monster_Spider.png", 4, 5, 0.1f);
		SpiderRenderer->CreateAnimation("Move_Spider_Down", "Monster_Spider.png", 0, 1, 0.1f);


		SpiderRenderer->ChangeAnimation("Idle_Spider");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 30, 15 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

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
			SpiderRenderer->ChangeAnimation("Idle_Spider");
		}
	);


	FSM.CreateState(SpiderState::MoveLeft, std::bind(&ASpider::Move, this, std::placeholders::_1),
		[this]()
		{
			SpiderRenderer->ChangeAnimation("Move_Spider_Left");
		}
	);

	FSM.CreateState(SpiderState::MoveRight, std::bind(&ASpider::Move, this, std::placeholders::_1),
		[this]()
		{
			SpiderRenderer->ChangeAnimation("Move_Spider_Right");
		}
	);

	FSM.ChangeState(SpiderState::Idle);
}

void ASpider::Tick(float _DeltaTime)
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

void ASpider::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.0f)
	{
		FSM.ChangeState(SpiderState::MoveRight);
		DelayTime = 0.0f;
	}
}

void ASpider::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 340.0f||
		PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -340.0f||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 170.0f||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -170.0f
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

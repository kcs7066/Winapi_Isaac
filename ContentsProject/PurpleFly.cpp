#include "PreCompile.h"
#include "PurpleFly.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>


APurpleFly::APurpleFly()
{
	SetActorLocation({ 200, 0 });

	{
		PurpleFlyRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PurpleFlyRenderer->SetSprite("Monster_Fly.png");
		PurpleFlyRenderer->SetComponentScale({ 100, 100 });
		PurpleFlyRenderer->CreateAnimation("Idle_PurpleFly", "Monster_Fly.png", 12,13, 0.1f);
		PurpleFlyRenderer->ChangeAnimation("Idle_PurpleFly");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50, 70 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

APurpleFly::~APurpleFly()
{
}

void APurpleFly::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(NewMonsterState::Idle, std::bind(&APurpleFly::Idle, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(NewMonsterState::Move, std::bind(&APurpleFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.ChangeState(NewMonsterState::Idle);
}

void APurpleFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	if (true == DeathCheck())
	{
		Destroy();
	}
}



void APurpleFly::Idle(float _DeltaTime)
{
	//if ()
	{
		//FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}




void APurpleFly::Move(float _DeltaTime)
{
	FVector2D Vector = FVector2D::ZERO;

	//if ()
	{
		Vector += FVector2D::RIGHT;
	}

	//if ()
	{
		Vector += FVector2D::LEFT;
	}
	//if ()
	{
		Vector += FVector2D::DOWN;
	}
	//if ()
	{
		Vector += FVector2D::UP;
	}


	//if ()
	{
		FSM.ChangeState(NewMonsterState::Idle);
		return;
	}
	AddActorLocation(Vector * _DeltaTime * Speed);

}
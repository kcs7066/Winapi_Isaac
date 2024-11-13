#include "PreCompile.h"
#include "Fly.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"


AFly::AFly()
{
	SetActorLocation({ 200, 0 });

	{
		FlyRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FlyRenderer->SetComponentScale({ 100, 100 });
		FlyRenderer->CreateAnimation("Move_Fly", "Monster_Fly.png", 0, 1, 0.1f);
		FlyRenderer->ChangeAnimation("Move_Fly");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 30, 30 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	DebugOn();
}

AFly::~AFly()
{
}

void AFly::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(FlyState::Idle, std::bind(&AFly::Idle, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(FlyState::Move, std::bind(&AFly::Move, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.ChangeState(FlyState::Move);
}

void AFly::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	if (true == DeathCheck())
	{
		Destroy();
	}
}



void AFly::Idle(float _DeltaTime)
{
	//if ()
	{
		//FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}




void AFly::Move(float _DeltaTime)
{




	RandomDir = { Random.Randomfloat(-1.0f, 1.0f) ,Random.Randomfloat(-1.0f, 1.0f) };

	RandomDir.Normalize();


	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 340.0f ||
		PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -340.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 170.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -170.0f
		)
	{

	}

	else
	{
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}


	

}
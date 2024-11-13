#include "PreCompile.h"
#include "RoundWorm.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include "MonsterTear.h"
#include "PlayGameMode.h"

ARoundWorm::ARoundWorm()
{
	SetActorLocation({ 200, 0 });

	{
		RoundWormRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RoundWormRenderer->SetSprite("Monster_RoundWorm.png");
		RoundWormRenderer->SetComponentScale({ 100, 100 });
		RoundWormRenderer->CreateAnimation("Idle_RoundWorm", "Monster_RoundWorm.png", 0, 1, 0.1f);
		RoundWormRenderer->CreateAnimation("Attack_RoundWorm", "Monster_RoundWorm.png", 3, 4, 0.1f);
		RoundWormRenderer->CreateAnimation("Move_RoundWorm", "Monster_RoundWorm.png", { 2,5,2 },{0.1f,0.8f,0.1f});
		RoundWormRenderer->ChangeAnimation("Idle_RoundWorm");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50, 90 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

}

ARoundWorm::~ARoundWorm()
{
}

void ARoundWorm::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(RoundWormState::Idle, std::bind(&ARoundWorm::Idle, this, std::placeholders::_1),
		[this]()
		{
			RoundWormRenderer->ChangeAnimation("Idle_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Attack, std::bind(&ARoundWorm::Attack, this, std::placeholders::_1),
		[this]()
		{
			RoundWormRenderer->ChangeAnimation("Attack_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Idle2, std::bind(&ARoundWorm::Idle2, this, std::placeholders::_1),
		[this]()
		{
			RoundWormRenderer->ChangeAnimation("Idle_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Move, std::bind(&ARoundWorm::Move, this, std::placeholders::_1),
		[this]()
		{
			RoundWormRenderer->ChangeAnimation("Move_RoundWorm");
		}
	);

	FSM.ChangeState(RoundWormState::Idle);
}

void ARoundWorm::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	BulletCoolTime -= _DeltaTime;
	if (true == DeathCheck())
	{
		Destroy();
	}
}



void ARoundWorm::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (DelayTime > 1.0f)
	{
		FSM.ChangeState(RoundWormState::Attack);
		DelayTime = 0.0f;
	}
}

void ARoundWorm::Attack(float _DeltaTime)
{
	if (BulletCoolTime < 0.0f)
	{
		AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
		NewTear->SetActorLocation(GetActorLocation());
		NewTear->Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
		BulletCoolTime = 0.5f;
	}

	DelayTime += _DeltaTime;
	if (DelayTime > 0.2f)
	{
		FSM.ChangeState(RoundWormState::Idle2);
		DelayTime = 0.0f;
	}
}

void ARoundWorm::Idle2(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (DelayTime > 0.6f)
	{
		FSM.ChangeState(RoundWormState::Move);
		DelayTime = 0.0f;
	}
}

void ARoundWorm::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	if (DelayTime > 0.9f)
	{

		FSM.ChangeState(RoundWormState::Idle);

		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		float NewX = Random.Randomfloat(-340.0f, 340.0f);
		float NewY = Random.Randomfloat(-170.0f, 170.0f);
		SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + NewX , PlayGameMode->CurRoom->RoomPos.Y + NewY });
		DelayTime = 0.0f;
	}



}

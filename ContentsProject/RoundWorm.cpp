#include "PreCompile.h"
#include "RoundWorm.h"

#include <EnginePlatform/EngineInput.h>
#include "MonsterTear.h"
#include "PlayGameMode.h"



ARoundWorm::ARoundWorm()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		
		MonsterRenderer->SetComponentScale({ 140, 140 });
		MonsterRenderer->SetComponentLocation({ 0, -20 });

		MonsterRenderer->CreateAnimation("Idle_RoundWorm", "Monster_RoundWorm.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Attack_RoundWorm", "Monster_RoundWorm.png", 2, 3, 0.1f);
		MonsterRenderer->CreateAnimation("Move_RoundWorm", "Monster_RoundWorm.png", { 4,5,4 },{0.1f,0.8f,0.1f});
		MonsterRenderer->CreateAnimation("Die_RoundWorm", "BloodPoof.png", 0, 10, 0.1f);

		MonsterRenderer->ChangeAnimation("Idle_RoundWorm");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 40, 40 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	DebugOn();

	SetHp(10.0f);
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
			MonsterRenderer->ChangeAnimation("Idle_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Attack, std::bind(&ARoundWorm::Attack, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Attack_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Idle2, std::bind(&ARoundWorm::Idle2, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Idle_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Move, std::bind(&ARoundWorm::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_RoundWorm");
		}
	);

	FSM.CreateState(RoundWormState::Die, std::bind(&ARoundWorm::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_RoundWorm");
		}
	);

	FSM.ChangeState(RoundWormState::Idle);
}

void ARoundWorm::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	BulletCoolTime -= _DeltaTime;
}



void ARoundWorm::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		FSM.ChangeState(RoundWormState::Die);
	}

	if (DelayTime > 1.0f)
	{
		FSM.ChangeState(RoundWormState::Attack);
		DelayTime = 0.0f;
	}
}

void ARoundWorm::Attack(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		FSM.ChangeState(RoundWormState::Die);
	}

	if (BulletCoolTime < 0.0f)
	{
		AMonsterTear* NewTear = GetWorld()->SpawnActor<AMonsterTear>();
		NewTear->SetActorLocation(GetActorLocation());
		NewTear->Dir = GetWorld()->GetPawn()->GetActorLocation() - GetActorLocation();
		NewTear->Dir.Normalize();
		
		BulletCoolTime = 0.5f;
	}

	if (DelayTime > 0.2f)
	{
		FSM.ChangeState(RoundWormState::Idle2);
		DelayTime = 0.0f;
	}
}

void ARoundWorm::Idle2(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		FSM.ChangeState(RoundWormState::Die);
	}

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
		float NewX = Random.Randomfloat(-338.0f, 338.0f);
		float NewY = Random.Randomfloat(-182.0f, 182.0f);
		SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + NewX , PlayGameMode->CurRoom->RoomPos.Y + NewY });
		DelayTime = 0.0f;
	}

}

void ARoundWorm::Die(float _DeltaTime)
{
	DeathValue = true;
	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
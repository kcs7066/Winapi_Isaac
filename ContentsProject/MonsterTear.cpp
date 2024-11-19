#include "PreCompile.h"
#include "MonsterTear.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include "Structure.h"
#include "Isaac.h"
#include "PlayGameMode.h"

AMonsterTear::AMonsterTear()
{

	{
		TearRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TearRenderer->SetComponentScale({ 80, 80 });
		TearRenderer->SetComponentLocation({ 0, -40 });


		TearRenderer->CreateAnimation("MonsterTear_Fly", "BloodTearPoof.png", 0, 0, 0.1f);
		TearRenderer->CreateAnimation("MonsterTear_Poof", "BloodTearPoof.png", 0, 14, 0.05f);
		TearRenderer->ChangeAnimation("MonsterTear_Fly");
	}

	{
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.2f);
	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 25, 25 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::Tear);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	}

}

AMonsterTear::~AMonsterTear()
{
}

void AMonsterTear::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(MonsterTearState::Fly, std::bind(&AMonsterTear::Fly, this, std::placeholders::_1),
		[this]()
		{
			TearRenderer->ChangeAnimation("MonsterTear_Fly");
		}
	);

	FSM.CreateState(MonsterTearState::Poof, std::bind(&AMonsterTear::Poof, this, std::placeholders::_1),
		[this]()
		{
			TearRenderer->ChangeAnimation("MonsterTear_Poof");
		}
	);

	int Value = Random.RandomInt(1, 2);

	if (1 == Value)
	{
		BGMPlayer = UEngineSound::Play("tear fire 1.wav");
	}
	else
	{
		BGMPlayer = UEngineSound::Play("tear fire 2.wav");
	}


	FSM.ChangeState(MonsterTearState::Fly);
}
void AMonsterTear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AMonsterTear::Fly(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	DropPos += _DeltaTime;
	float Value = -40.0f + DropPos * DropPos * 60.0f;

	TearRenderer->SetComponentLocation({ 0.0f, Value });

	if (DelayTime < 0.8f)
	{
		AActor* ResultStructure = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);
		if (nullptr != ResultStructure)
		{
			DelayTime = 0.0f;
			FSM.ChangeState(MonsterTearState::Poof);
			BGMPlayer = UEngineSound::Play("tear block.wav");
		}

		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);
		if (nullptr != Result)
		{
			
			AIsaac* Ptr = GetWorld()->GetPawn<AIsaac>();
			if (0.0f >= Ptr->HitCoolTime)
			{
				Ptr->Hp--;
				Ptr->HitStart();
			}
			DelayTime = 0.0f;
			FSM.ChangeState(MonsterTearState::Poof);
			BGMPlayer = UEngineSound::Play("tear block.wav");

		}
		else
		{
			FVector2D NewLocation = GetActorLocation() += Dir * _DeltaTime * TearSpeed;
			APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

			if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 338.0f ||
				PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -338.0f ||
				PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 182.0f ||
				PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -182.0f
				)
			{
				DelayTime = 0.0f;
				FSM.ChangeState(MonsterTearState::Poof);
				BGMPlayer = UEngineSound::Play("tear block.wav");
			}
			else
			{
				AddActorLocation(Dir * _DeltaTime * TearSpeed);
			}
		}

	}
	else
	{
		DelayTime = 0.0f;
		FSM.ChangeState(MonsterTearState::Poof);
		BGMPlayer = UEngineSound::Play("tear block.wav");
	}
}

void AMonsterTear::Poof(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 0.75f)
	{

		Destroy();
	}
}
#include "PreCompile.h"
#include "Tear.h"
#include <EngineCore/SpriteRenderer.h>
#include "Isaac.h"
#include "ContentsEnum.h"
#include "PlayGameMode.h"
#include "Monster.h"
#include "Structure.h"

ATear::ATear()
{	
	
    {
		TearRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TearRenderer->SetComponentScale({ 80, 80 });
		TearRenderer->SetComponentLocation({ 0, -40 });

		TearRenderer->CreateAnimation("Tear_Fly", "Tear.png", 5, 5, 0.1f);
		TearRenderer->CreateAnimation("Tear_Poof", "TearPoof.png", 0, 14, 0.05f);
		TearRenderer->ChangeAnimation("Tear_Fly");
	}
	{
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.2f);
	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 25, 25 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::Tear);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	}

}

ATear::~ATear()
{
}

void ATear::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(TearState::Fly, std::bind(&ATear::Fly, this, std::placeholders::_1),
		[this]()
		{
			TearRenderer->ChangeAnimation("Tear_Fly");
		}
	);

	FSM.CreateState(TearState::Poof, std::bind(&ATear::Poof, this, std::placeholders::_1),
		[this]()
		{
			TearRenderer->ChangeAnimation("Tear_Poof");
		}
	);

	FSM.ChangeState(TearState::Fly);
}
void ATear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);

}

void ATear::Fly(float _DeltaTime)
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
			FSM.ChangeState(TearState::Poof);
		}

		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Monster);
		if (nullptr != Result)
		{
			AMonster* NewResult = dynamic_cast<AMonster*>(Result);

			AIsaac* Ptr =  GetWorld()->GetPawn<AIsaac>();

			if (nullptr != Ptr)
			{
				NewResult->Hp -= Ptr->Damage;
				DelayTime = 0.0f;
				FSM.ChangeState(TearState::Poof);
			}
			else {
				int a = 0;
			}
		}
		else
		{
			FVector2D NewLocation = GetActorLocation() += Dir * _DeltaTime * Speed;
			APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

			if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 338.0f ||
				PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -338.0f ||
				PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 182.0f ||
				PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -182.0f
				)
			{
				DelayTime = 0.0f;
				FSM.ChangeState(TearState::Poof);
			}
			else
			{
				AddActorLocation(Dir * _DeltaTime * Speed);
			}
		}
	}
	else
	{
		DelayTime = 0.0f;
		FSM.ChangeState(TearState::Poof);
	}
}

void ATear::Poof(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 0.75f)
	{
		Destroy();
	}
}
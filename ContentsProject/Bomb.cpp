#include "PreCompile.h"
#include "Bomb.h"
#include "ContentsEnum.h"
#include <EngineCore/SpriteRenderer.h>
#include "Monster.h"
#include "Isaac.h"

ABomb::ABomb()
{

	{
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.3f);
	}


	BombRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BombRenderer->SetOrder(ERenderOrder::BOMB);
	BombRenderer->SetComponentScale({ 70, 70 });
	BombRenderer->SetComponentLocation({ 2, -16 });

	BombRenderer->CreateAnimation("Idle_Bomb", "Pickup_Bomb.png", 0, 0, 0.1f);
	BombRenderer->CreateAnimation("Explosion_Bomb", "Effect_Explosion.png", 0, 11, 0.04f);
	BombRenderer->ChangeAnimation("Idle_Bomb");

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 200, 200 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::Bomb);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	}
}


ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{

	Super::BeginPlay();

	FSM.CreateState(BombState::Idle, std::bind(&ABomb::Idle, this, std::placeholders::_1),
		[this]()
		{
			BombRenderer->ChangeAnimation("Idle_Bomb");
		}
	);

	FSM.CreateState(BombState::Explosion, std::bind(&ABomb::Explosion, this, std::placeholders::_1),
		[this]()
		{
	
		}
	);

	FSM.CreateState(BombState::ExplosionStay, std::bind(&ABomb::ExplosionStay, this, std::placeholders::_1),
		[this]()
		{
			BombRenderer->ChangeAnimation("Explosion_Bomb");
		}
	);

	FSM.ChangeState(BombState::Idle);
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void ABomb::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.6f)
	{
		DelayTime = 0.0f;
		FSM.ChangeState(BombState::Explosion);
	}
}

void ABomb::Explosion(float _DeltaTime)
{

	std::vector<AActor*> Results = CollisionComponent->CollisionAll(ECollisionGroup::Monster, { 0,0 });

	if (false == Results.empty())
	{

		std::vector<AActor*>::iterator StartIter = Results.begin();
		std::vector<AActor*>::iterator EndIter = Results.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AMonster* NewResult = dynamic_cast<AMonster*>(*StartIter);
			NewResult->Hp -= 60.0f;
		}
	}

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);
		NewResult->Hp -= 2;
		NewResult->HitStart();
	}

	FSM.ChangeState(BombState::ExplosionStay);
}

void ABomb::ExplosionStay(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	BombRenderer->SetComponentScale({ 275, 275 });
	BombRenderer->SetComponentLocation({ 0,-60 });
	if (DelayTime > 0.48f)
	{
		Destroy();
	}
}

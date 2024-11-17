#include "PreCompile.h"
#include "Bomb.h"
#include "ContentsEnum.h"
#include <EngineCore/SpriteRenderer.h>

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
		CollisionComponent->SetComponentScale({ 50, 50 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::Tear);
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
	BombRenderer->SetComponentScale({ 275, 275 });
	BombRenderer->SetComponentLocation({ 0,-60 });
	DelayTime += _DeltaTime;
	if (DelayTime > 0.48f)
	{

		Destroy();
	}
}

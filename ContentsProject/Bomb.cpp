#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"
#include "Monster.h"
#include "Isaac.h"
#include "Structure.h"
#include "Poop.h"
#include "Rock.h"
 
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
		ExplosionStart();
	}
}

void ABomb::ExplosionStart()
{
	int RandomValue = Random.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		EffectPlayer = UEngineSound::Play("boss explosions 0.wav");
		break;
	case 2:
		EffectPlayer = UEngineSound::Play("boss explosions 1.wav");
		break;
	default:
		EffectPlayer = UEngineSound::Play("boss expolsions 2.wav");
		break;
	}
	


	std::vector<AActor*> Results = CollisionComponent->CollisionAll(ECollisionGroup::Monster, FVector2D::ZERO);

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

		if (0.0f >= NewResult->HitCoolTime)
		{
			NewResult->Hp -= 2;
			NewResult->HitStart();
		}
	}

	std::vector<AActor*> StructureResults = CollisionComponent->CollisionAll(ECollisionGroup::Structure, FVector2D::ZERO);
	if (false == StructureResults.empty())
	{

		std::vector<AActor*>::iterator StartIter = StructureResults.begin();
		std::vector<AActor*>::iterator EndIter = StructureResults.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AStructure* NewStructureResult = dynamic_cast<AStructure*>(*StartIter);
			NewStructureResult->Hp = 0;

			APoop* ResultPoop = dynamic_cast<APoop*>(NewStructureResult);
			ARock* ResultRock = dynamic_cast<ARock*>(NewStructureResult);
			if (nullptr != ResultPoop)
			{
					ResultPoop->StructureRenderer->ChangeAnimation("Poop0");
					ResultPoop->CollisionComponent->SetActive(false);
			}
			else if(nullptr != ResultRock)
			{
				ResultRock->StructureRenderer->ChangeAnimation("Rock0");
				ResultRock->CollisionComponent->SetActive(false);
				CrumblePlayer = UEngineSound::Play("rock crumble 0.wav");
			}

		}
	}

	FSM.ChangeState(BombState::Explosion);
}

void ABomb::Explosion(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	BombRenderer->SetComponentScale({ 275, 275 });
	BombRenderer->SetComponentLocation({ 0,-60 });
	if (DelayTime > 0.48f)
	{
		Destroy();
	}
}

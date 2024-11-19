#include "PreCompile.h"
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"


AMonster::AMonster()
	: AActor()

{
	SetActorLocation({ 200, 0 });

	MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50, 50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");

}

AMonster::~AMonster()
{
}


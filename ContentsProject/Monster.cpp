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


	PoofRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PoofRenderer->SetOrder(ERenderOrder::MONSTERFRONT);
	PoofRenderer->SetComponentScale({ 100,100 });
	PoofRenderer->SetComponentLocation({ 0,-50 });
	PoofRenderer->CreateAnimation("Poof", "Effect_Poof.png", 0, 14, 0.05f);
	PoofRenderer->ChangeAnimation("Poof");
	PoofRenderer->Destroy(0.75f);

}

AMonster::~AMonster()
{
}

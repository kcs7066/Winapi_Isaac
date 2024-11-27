#include "PreCompile.h"
#include "Item.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"

AItem::AItem()
{
	ItemRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemRenderer->SetOrder(ERenderOrder::ITEM);
	ItemRenderer->SetComponentLocation({ 0,-50 });

	AlterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	AlterRenderer->SetOrder(ERenderOrder::ITEM);
	AlterRenderer->SetSprite("ItemAlter.png");
	AlterRenderer->SetSpriteScale(2.0f);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 33, 33 });
	CollisionComponent->SetComponentLocation({ 0,-3 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Item);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");
}

AItem::~AItem()
{
}


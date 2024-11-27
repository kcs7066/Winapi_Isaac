#include "PreCompile.h"
#include "Structure.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"

AStructure::AStructure()
	: AActor()
{
	StructureRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StructureRenderer->SetOrder(ERenderOrder::STRUCTURE);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Structure);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

AStructure::~AStructure()
{
}


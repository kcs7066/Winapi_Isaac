#include "PreCompile.h"
#include "Structure.h"
#include "ContentsEnum.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>


AStructure::AStructure()
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


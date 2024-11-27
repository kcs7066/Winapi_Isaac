#include "PreCompile.h"
#include "Rock.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"


ARock::ARock()
	:AStructure()
{
	StructureRenderer->SetComponentScale({ 75, 75 });
	StructureRenderer->CreateAnimation("Rock4", "Structure_Rock.png", 0, 0, 0.1f);
	StructureRenderer->CreateAnimation("Rock0", "Structure_Rock.png", 3, 3, 0.1f);
	StructureRenderer->ChangeAnimation("Rock4");

	CollisionComponent->SetComponentScale({ 50,50 });

	DebugOn();
}

ARock::~ARock()
{
}


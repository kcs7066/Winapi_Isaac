#include "PreCompile.h"
#include "Poop.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"


APoop::APoop()
	:AStructure()
{
	StructureRenderer->SetComponentScale({ 75, 75 });
	StructureRenderer->CreateAnimation("Poop4", "Structure_Poop_1.png", 0, 0, 0.1f);
	StructureRenderer->CreateAnimation("Poop3", "Structure_Poop_1.png", 1, 1, 0.1f);
	StructureRenderer->CreateAnimation("Poop2", "Structure_Poop_1.png", 2, 2, 0.1f);
	StructureRenderer->CreateAnimation("Poop1", "Structure_Poop_1.png", 3, 3, 0.1f);
	StructureRenderer->CreateAnimation("Poop0", "Structure_Poop_1.png", 4, 4, 0.1f);
	StructureRenderer->ChangeAnimation("Poop4");
	
	CollisionComponent->SetComponentScale({ 50,50 });

	DebugOn();
}

APoop::~APoop()
{
}



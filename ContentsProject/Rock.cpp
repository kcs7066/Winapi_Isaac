#include "PreCompile.h"
#include "Rock.h"
#include "ContentsEnum.h"

ARock::ARock()
{


	{
		RockRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RockRenderer->SetOrder(ERenderOrder::STRUCTURE);
		RockRenderer->SetComponentScale({ 75, 75 });
		RockRenderer->CreateAnimation("Idle_Rock", "Structure_Rock.png", 0, 0, 0.1f);
		RockRenderer->ChangeAnimation("Idle_Rock");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Structure);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

ARock::~ARock()
{
}


#include "PreCompile.h"
#include "Poop.h"
#include "ContentsEnum.h"

APoop::APoop()
{

	{
		PoopRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PoopRenderer->SetOrder(ERenderOrder::STRUCTURE);
		PoopRenderer->SetComponentScale({ 75, 75 });
		PoopRenderer->CreateAnimation("Idle_Poop", "Structure_Poop_1.png", 0, 0, 0.1f);
		PoopRenderer->ChangeAnimation("Idle_Poop");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Structure);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

APoop::~APoop()
{
}


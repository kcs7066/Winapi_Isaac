#include "PreCompile.h"
#include "Poop.h"
#include "ContentsEnum.h"

APoop::APoop()
{
	SetActorLocation({ 200, 0 });

	{
		PoopRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PoopRenderer->SetComponentScale({ 75, 75 });
		PoopRenderer->CreateAnimation("Idle_Poop", "Structure_Poop_1.png", 0, 0, 0.1f);
		PoopRenderer->ChangeAnimation("Idle_Poop");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Structure);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

APoop::~APoop()
{
}


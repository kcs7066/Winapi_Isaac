#include "PreCompile.h"
#include "Rock.h"
#include "ContentsEnum.h"

ARock::ARock()
{
	SetActorLocation({ 200, 0 });

	{
		RockRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RockRenderer->SetComponentScale({ 75, 75 });
		RockRenderer->CreateAnimation("Idle_Rock", "Structure_Rock.png", 0, 0, 0.1f);
		RockRenderer->ChangeAnimation("Idle_Rock");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Structure);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

ARock::~ARock()
{
}

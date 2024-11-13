#include "PreCompile.h"
#include "Rock.h"
#include "ContentsEnum.h"

ARock::ARock()
{
	SetActorLocation({ 200, 0 });

	{
		RockRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RockRenderer->SetComponentScale({ 100, 100 });
		RockRenderer->CreateAnimation("Idle_Rock", "Structure_Rock.png", 0, 0, 0.1f);
		RockRenderer->ChangeAnimation("Idle_Rock");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 52, 52 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

ARock::~ARock()
{
}


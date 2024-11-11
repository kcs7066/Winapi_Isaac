#include "PreCompile.h"
#include "Door.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

ADoor::ADoor()
{

	
	USpriteRenderer* DoorRenderer = CreateDefaultSubObject<USpriteRenderer>();
	DoorRenderer->SetOrder(ERenderOrder::DOOR);
	DoorRenderer->SetSprite("NormalRoomDoor.png");
	DoorRenderer->SetSpriteScale(1.0f);

	
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation(this->GetActorLocation());
	CollisionComponent->SetComponentScale({ 50, 70 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Door);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ADoor::~ADoor()
{
}


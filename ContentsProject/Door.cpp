#include "PreCompile.h"
#include "Door.h"
#include "ContentsEnum.h"



ADoor::ADoor()
{

	
	DoorRenderer = CreateDefaultSubObject<USpriteRenderer>();
	DoorRenderer->SetOrder(ERenderOrder::DOOR);
	DoorRenderer->SetSprite("BossRoomDoor.png");
	DoorRenderer->SetSpriteScale(1.0f);


	
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50, 50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Door);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

ADoor::~ADoor()
{
}

void ADoor::DoorOpen()
{
	switch (Dir)
	{
	case DoorDir::NONE:
		break;
	case DoorDir::UP:
		DoorRenderer->CreateAnimation("UpNormalRoomDoor_Open", "BossRoomDoor.png", 2, 2, 0.1f);
		DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Open");
		break;
	case DoorDir::RIGHT:
		DoorRenderer->CreateAnimation("RightNormalRoomDoor_Open", "BossRoomDoor.png", 1, 1, 0.1f);
		DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Open");
		break;
	case DoorDir::DOWN:
		DoorRenderer->CreateAnimation("DownNormalRoomDoor_Open", "BossRoomDoor.png", 3, 3, 0.1f);
		DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Open");
		break;
	case DoorDir::LEFT:
		DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Open", "BossRoomDoor.png", 0, 0, 0.1f);
		DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Open");
		break;
	default:
		break;
	}

}

void ADoor::DoorClose()
{
	switch (Dir)
	{
	case DoorDir::NONE:
		break;
	case DoorDir::UP:
		DoorRenderer->CreateAnimation("UpNormalRoomDoor_Close", "BossRoomDoor.png", 6, 6, 0.1f);
		DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Close");
		break;
	case DoorDir::RIGHT:
		DoorRenderer->CreateAnimation("RightNormalRoomDoor_Close", "BossRoomDoor.png", 5, 5, 0.1f);
		DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Close");
		break;
	case DoorDir::DOWN:
		DoorRenderer->CreateAnimation("DownNormalRoomDoor_Close", "BossRoomDoor.png", 7, 7, 0.1f);
		DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Close");
		break;
	case DoorDir::LEFT:
		DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Close", "BossRoomDoor.png", 4, 4, 0.1f);
		DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Close");
		break;
	default:
		break;
	}

}
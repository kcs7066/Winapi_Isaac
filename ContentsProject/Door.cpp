#include "PreCompile.h"
#include "Door.h"
#include "ContentsEnum.h"



ADoor::ADoor()
{

	
	DoorRenderer = CreateDefaultSubObject<USpriteRenderer>();
	DoorRenderer->SetOrder(ERenderOrder::DOOR);
	DoorRenderer->SetSprite("NormalRoomDoor.png");
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
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("UpBossRoomDoor_Open", "BossRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpBossRoomDoor_Open");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("UpGoldRoomDoor_Open", "GoldRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpGoldRoomDoor_Open");
		}
		else
		{
			DoorRenderer->CreateAnimation("UpNormalRoomDoor_Open", "NormalRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Open"); 
		}
		break;
	case DoorDir::RIGHT:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("RightBossRoomDoor_Open", "BossRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightBossRoomDoor_Open");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("RightGoldRoomDoor_Open", "GoldRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightGoldRoomDoor_Open");
		}
		else
		{
			DoorRenderer->CreateAnimation("RightNormalRoomDoor_Open", "NormalRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Open");
		}
		break;
	case DoorDir::DOWN:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("DownBossRoomDoor_Open", "BossRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownBossRoomDoor_Open");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("DownGoldRoomDoor_Open", "GoldRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownGoldRoomDoor_Open");
		}
		else
		{
			DoorRenderer->CreateAnimation("DownNormalRoomDoor_Open", "NormalRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Open"); 
		}
		break;
	case DoorDir::LEFT:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("LeftBossRoomDoor_Open", "BossRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftBossRoomDoor_Open");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("LeftGoldRoomDoor_Open", "GoldRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftGoldRoomDoor_Open");
		}
		else
		{
			DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Open", "NormalRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Open");
		}
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
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("UpBossRoomDoor_Close", "BossRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpBossRoomDoor_Close");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("UpGoldRoomDoor_Close", "GoldRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpGoldRoomDoor_Close");
		}
		else
		{
			DoorRenderer->CreateAnimation("UpNormalRoomDoor_Close", "NormalRoomDoor.png", 2, 2, 0.1f);
			DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Close");
		}
		break;
	case DoorDir::RIGHT:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("RightBossRoomDoor_Close", "BossRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightBossRoomDoor_Close");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("RightGoldRoomDoor_Close", "GoldRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightGoldRoomDoor_Close");
		}
		else
		{
			DoorRenderer->CreateAnimation("RightNormalRoomDoor_Close", "NormalRoomDoor.png", 1, 1, 0.1f);
			DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Close");
		}
		break;
	case DoorDir::DOWN:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("DownBossRoomDoor_Close", "BossRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownBossRoomDoor_Close");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("DownGoldRoomDoor_Close", "GoldRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownGoldRoomDoor_Close");
		}
		else
		{
			DoorRenderer->CreateAnimation("DownNormalRoomDoor_Close", "NormalRoomDoor.png", 3, 3, 0.1f);
			DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Close");
		}
		break;
	case DoorDir::LEFT:
		if (DoorType::BOSS == Type)
		{
			DoorRenderer->CreateAnimation("LeftBossRoomDoor_Close", "BossRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftBossRoomDoor_Close");
		}
		else if (DoorType::GOLD == Type)
		{
			DoorRenderer->CreateAnimation("LeftGoldRoomDoor_Close", "GoldRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftGoldRoomDoor_Close");
		}
		else
		{
			DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Close", "NormalRoomDoor.png", 0, 0, 0.1f);
			DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Close");
		}
		break;
	default:
		break;
	}
}
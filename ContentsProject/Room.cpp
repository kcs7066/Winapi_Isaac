#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "PlayGameMode.h"
#include "ContentsEnum.h"

ARoom::ARoom()
{

	{

	}

}

ARoom::~ARoom()
{
}

void ARoom::CreateDoor(RoomDir _Dir, FVector2D _Pos)
{
	ADoor* NewDoor = GetWorld()->SpawnActor<ADoor>();
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::DOOR);
	SpriteRenderer->SetSprite("NormalRoomDoor.png");
	SpriteRenderer->SetSpriteScale(1.0f);
	SetActorLocation({0,0});

	switch (_Dir)
	{
	case RoomDir::NONE:
		break;
	case RoomDir::UP:
		SpriteRenderer->CreateAnimation("UpNormalRoomDoor_Idle", "NormalRoomDoor.png", 2, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("UpNormalRoomDoor_Idle");
		SpriteRenderer->SetComponentLocation({ _Pos.X, _Pos.Y - 215.0f });

		break;
	case RoomDir::RIGHT:
		SpriteRenderer->CreateAnimation("RightNormalRoomDoor_Idle", "NormalRoomDoor.png", 1, 1, 0.1f);
		SpriteRenderer->ChangeAnimation("RightNormalRoomDoor_Idle");
		SpriteRenderer->SetComponentLocation({ _Pos.X + 370.0f, _Pos.Y });

		break;
	case RoomDir::DOWN:
		SpriteRenderer->CreateAnimation("DownNormalRoomDoor_Idle", "NormalRoomDoor.png", 3, 3, 0.1f);
		SpriteRenderer->ChangeAnimation("DownNormalRoomDoor_Idle");
		SpriteRenderer->SetComponentLocation({ _Pos.X, _Pos.Y + 215.0f });

		break;
	case RoomDir::LEFT:
		SpriteRenderer->CreateAnimation("LeftNormalRoomDoor_Idle", "NormalRoomDoor.png", 0, 0, 0.1f);
		SpriteRenderer->ChangeAnimation("LeftNormalRoomDoor_Idle");
		SpriteRenderer->SetComponentLocation({ _Pos.X - 370.0f, _Pos.Y });

		break;
	default:
		break;
	}

	Doors.insert({ _Dir,NewDoor });
}

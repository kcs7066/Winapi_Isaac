#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ARoom::ARoom()
{

	{

	}

}

ARoom::~ARoom()
{
}

void ARoom::Link(ARoom* _Room, RoomDir _Dir)
{

	switch (_Dir)
	{
	case RoomDir::UP:
		LinkedRooms.insert({ RoomDir::UP,_Room });
		break;
	case RoomDir::RIGHT:
		LinkedRooms.insert({ RoomDir::RIGHT, _Room });
		break;
	case RoomDir::DOWN:
		LinkedRooms.insert({ RoomDir::DOWN, _Room });
		break;
	case RoomDir::LEFT:
		LinkedRooms.insert({ RoomDir::LEFT, _Room });
		break;
	default:
		break;
	}
}

void ARoom::InterLink(ARoom* _Room, RoomDir _Dir)
{
	this->Link(_Room, _Dir);
	_Room->Link(this, ReverseDir(_Dir));

	int a = 0;
}
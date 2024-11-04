#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ARoom::ARoom()
{

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Room_01.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

}

ARoom::~ARoom()
{
}

void ARoom::Link(ARoom* _Room, RoomDir _Dir)
{

	switch (_Dir)
	{
	case RoomDir::LEFT:
		Rooms.insert({ RoomDir::LEFT,_Room });
		break;
	case RoomDir::RIGHT:
		Rooms.insert({ RoomDir::RIGHT, _Room });
		break;
	case RoomDir::UP:
		Rooms.insert({ RoomDir::UP, _Room });
		break;
	case RoomDir::DOWN:
		Rooms.insert({ RoomDir::DOWN, _Room });
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
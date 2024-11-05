#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "Player.h"

enum class RoomDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX,
};

class ARoom : public AActor
{
public:
	// constrcuter destructer
	ARoom();
	~ARoom();

	// delete Function
	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	void Link(ARoom* _Room, RoomDir _Dir);
	void InterLink(ARoom* _Room, RoomDir _Dir);

	RoomDir ReverseDir(RoomDir _Dir)
	{
		switch (_Dir)
		{
		case RoomDir::LEFT:
			return RoomDir::RIGHT;
			break;
		case RoomDir::RIGHT:
			return RoomDir::LEFT;
			break;
		case RoomDir::UP:
			return RoomDir::DOWN;
			break;
		case RoomDir::DOWN:
			return RoomDir::UP;
			break;
		default:
			break;
		}
	}

	bool IsLink()
	{
		return true;
	}

	std::map<RoomDir, ARoom*> LinkedRooms;
protected:

private:


};


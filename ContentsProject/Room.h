#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "Player.h"
#include "Door.h"

enum class RoomDir
{
	NONE = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4
	
};

enum class RoomValue
{
	RoomQUANTITY = 8
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
			return RoomDir::NONE;
			break;
		}
	}

	void CreateDoor(RoomDir _Dir, FVector2D _Pos, ARoom* _LinkRoom);

	FVector2D NomalizedRoomPos;
	FVector2D RoomPos;
	
	std::map<RoomDir, ARoom*> LinkedRooms;
	std::map<RoomDir, ADoor*> Doors;

protected:

private:

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

}; 


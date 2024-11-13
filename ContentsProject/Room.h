#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "Door.h"

enum class RoomDir
{
	NONE = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4
	
};

enum class RoomType
{
	NORMAL,
	GOLD,
	BOSS
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

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



	void CreateDoor(RoomDir _Dir, FVector2D _Pos, ARoom* _LinkRoom);



	FVector2D NomalizedRoomPos;
	FVector2D RoomPos;
	
	std::map<RoomDir, ARoom*> LinkedRooms;
	std::map<RoomDir, ADoor*> Doors;

	USpriteRenderer* RoomRenderer;

	RoomType Type = RoomType::NORMAL;

	int MonsterNumber = 0;

	int SpiderNumber = 0;

	int CanSpawnNumber = 1;

	bool RoomClear = true;

protected:

private:

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	

}; 


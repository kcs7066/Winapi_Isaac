#pragma once


#include <EngineCore/GameMode.h>
#include "Room.h"
#include <EngineBase/EngineRandom.h>

class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	bool IsBind(FVector2D _Pos)
	{
		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == _Pos)
					return true;
			}
		}
		return false;
	}

	bool IsAdjacentTwice(FVector2D _Pos)
	{
		int AdjacentRoom = 0;
		FVector2D AdjacentPos1 = { _Pos.X + 1 , _Pos.Y };
		FVector2D AdjacentPos2 = { _Pos.X - 1 , _Pos.Y };
		FVector2D AdjacentPos3 = { _Pos.X , _Pos.Y + 1 };
		FVector2D AdjacentPos4 = { _Pos.X , _Pos.Y - 1 };

		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == AdjacentPos1)
					AdjacentRoom++;
			}
		}

		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == AdjacentPos2)
					AdjacentRoom++;
			}
		}
		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == AdjacentPos3)
					AdjacentRoom++;
			}
		}
		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == AdjacentPos4)
					AdjacentRoom++;
			}
		}

		if (AdjacentRoom == 1)
		{
			return false;
		}
		return true;
	}
	//void SetCurRoom(class ARoom* _Room)
	//{
	//	CurRoom = _Room;
	//}

	//ARoom* GetCurRoom()
	//{
	//	return CurRoom;
	//}


protected:
	
private:
	
	std::map<std::string_view, ARoom*> Rooms;
	std::map<int, FVector2D> RoomBind;

	ARoom* PrevRoom = nullptr;
	void CreateBossRoomPath();
	void CreateRestRoomPath(int _RoomNumber);
	ARoom* CreateRoom(std::string_view _RoomName,FVector2D _Pos);
	UEngineRandom Random;

	

	int RoomNumber = 0;

};

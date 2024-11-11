#pragma once


#include <EngineCore/GameMode.h>
#include "Room.h"
#include "Door.h"
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

	void Link(ARoom* _Room);

	bool IsBind(FVector2D _Pos)
	{
		{
			std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
			std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				if (StartIter->second == _Pos)
				{
					return true;
				}
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
	
	int Roomkey(FVector2D _Pos)
	{
		std::map<int, FVector2D>::iterator StartIter = RoomBind.begin();
		std::map<int, FVector2D>::iterator EndIter = RoomBind.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second == _Pos)
				return StartIter->first;
		}
	}
	
	ARoom* CurRoom = nullptr;

protected:
	
private:

	
	ARoom* PrevRoom = nullptr;
	float RoomMoveCameraTime = 0.0f;

	std::map<int, ARoom*> Rooms;
	std::map<int, FVector2D> RoomBind;


	void CreateBossRoomPath();
	void CreateRestRoomPath(int _RoomNumber);
	void CreateRoom(std::string_view _RoomName,FVector2D _Pos);

	USpriteRenderer* SpriteRenderer;

	UEngineRandom Random;

	

	int RoomNumber = 0;

	
};


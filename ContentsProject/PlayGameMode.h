#pragma once


#include <EngineCore/GameMode.h>
#include "Fade.h"
#include "Room.h"
#include "Door.h"
#include "Monster.h"
#include <EnginePlatform/EngineSound.h>
#include <EngineBase/EngineRandom.h>
#include "RoundWorm.h"
#include "Dip.h"
#include "Larryjr.h"
#include "Ui.h"


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

	ARoom* PrevRoom = nullptr;
	ARoom* CurRoom = nullptr;
	std::map<int, ARoom*> Rooms;

	USoundPlayer BGMPlayer;

	class AUi* HeartUi;
	class AUi* SecondHeartUi;
	class AUi* ThirdHeartUi;
	class AUi* CoinUi;
	class AUi* BombUi;
	class AUi* KeyUi;

	void CreateMap();
	void CreateItem();

	AFade* Fade;
	USpriteRenderer* RestartGameRenderer = nullptr;
	bool DeathValue = false;

protected:
	
private:
	
	std::map<int, FVector2D> RoomBind;


	void CreateBossRoomPath();
	void CreateRestRoomPath(int _RoomNumber);
	void CreateRoom(std::string_view _RoomName,FVector2D _Pos,RoomType _Type = RoomType::NORMAL);


	template<typename ActorType>
	ActorType* SetMonster(FVector2D _Pos)
	{
		CurRoom->MonsterNumber++;
		ActorType* NewActor = GetWorld()->SpawnActor<ActorType>();
		
		NewActor->SetActorLocation(_Pos);	
		NewActor->Random.SetSeed(time(nullptr) + SeedValue);

		SeedValue++;

		return NewActor;	
	}

	template<typename ActorType>
	void SetStructure(FVector2D _Pos)
	{
		ActorType* NewActor = GetWorld()->SpawnActor<ActorType>();
		NewActor->SetActorLocation(_Pos);
		NewActor->Pos = _Pos;
	}

	UEngineRandom Random;
	USpriteRenderer* SpriteRenderer = nullptr;
	USpriteRenderer* MapRenderer = nullptr;
	USpriteRenderer* BossMiniMapRenderer = nullptr;
	USpriteRenderer* GoldMiniMapRenderer = nullptr;
	USpriteRenderer* PauseGameRenderer = nullptr;


	bool PauseGame = false;
	bool ExitGameValue = false;

	float RoomMoveCameraTime = 0.0f;

	int RoomNumber = 0;

	ALarryjr* Monster0 = nullptr;
	ALarryjr* Monster1 = nullptr;
	ALarryjr* Monster2 = nullptr;
	ALarryjr* Monster3 = nullptr;
	ALarryjr* Monster4 = nullptr;
	ALarryjr* Monster5 = nullptr;
	ALarryjr* Monster6 = nullptr;
	ALarryjr* Monster7 = nullptr;
	long long SeedValue = 0;

	int SpawnCaseValue = 1;

};


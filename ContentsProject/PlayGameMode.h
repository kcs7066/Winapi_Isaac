#pragma once
#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/GameMode.h>

#include "Room.h"
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
	bool IsBind(FVector2D _Pos);
	bool IsAdjacentTwice(FVector2D _Pos);
	int Roomkey(FVector2D _Pos);

	class ARoom* PrevRoom = nullptr;
	class ARoom* CurRoom = nullptr;
	class USpriteRenderer* RestartGameRenderer = nullptr;
	class AUi* HeartUi = nullptr;
	class AUi* SecondHeartUi = nullptr;
	class AUi* ThirdHeartUi = nullptr;
	class AUi* BombUi = nullptr;
	class AFade* Fade = nullptr;

	std::vector<class ARoom*> Rooms;

	USoundPlayer BGMPlayer;
	USoundPlayer EffectPlayer;

	bool DeathValue = false;

protected:
	
private:
	
	int SpawnCaseValue = 1;
	long long SeedValue = 0;

	float RoomMoveCameraTime = 0.0f;

	bool PauseGame = false;
	bool ExitGameValue = false;

	std::vector<FVector2D> NormalizedRoom;

	class USpriteRenderer* SpriteRenderer = nullptr;
	class USpriteRenderer* MapRenderer = nullptr;
	class USpriteRenderer* BossMiniMapRenderer = nullptr;
	class USpriteRenderer* GoldMiniMapRenderer = nullptr;
	class USpriteRenderer* PauseGameRenderer = nullptr;

	class ALarryjr* Monster0 = nullptr;
	class ALarryjr* Monster1 = nullptr;
	class ALarryjr* Monster2 = nullptr;
	class ALarryjr* Monster3 = nullptr;
	class ALarryjr* Monster4 = nullptr;
	class ALarryjr* Monster5 = nullptr;
	class ALarryjr* Monster6 = nullptr;
	class ALarryjr* Monster7 = nullptr;

	UEngineRandom Random;

	void CreateMap();
	void CreateItem();
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

};


#pragma once


#include <EngineCore/GameMode.h>
#include "Room.h"

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

	void BeginPlay();

	void Tick(float _DeltaTime);

	void SetCurRoom(class ARoom* _Room)
	{
		CurRoom = _Room;
	}

	ARoom* CurRoom = nullptr;

protected:

private:

	
};

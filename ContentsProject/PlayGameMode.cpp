#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "PlayMap.h"
#include "Room.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}


void APlayGameMode::BeginPlay()
{
	ARoom* FirstRoom = GetWorld()->SpawnActor<ARoom>();

    ARoom* RoomE = GetWorld()->SpawnActor<ARoom>();
	ARoom* RoomW = GetWorld()->SpawnActor<ARoom>();
	ARoom* RoomS = GetWorld()->SpawnActor<ARoom>();
	ARoom* RoomN = GetWorld()->SpawnActor<ARoom>();


	FirstRoom->InterLink(RoomE, RoomDir::RIGHT);
	FirstRoom->InterLink(RoomW, RoomDir::LEFT);
	FirstRoom->InterLink(RoomS, RoomDir::DOWN);
	FirstRoom->InterLink(RoomN, RoomDir::UP);
	
	SetCurRoom(FirstRoom);
	FirstRoom->SetName("FirstRoom");

	int a = 0;
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{
	}

}




#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "PlayMap.h"
#include "Room.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineMath.h>


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}


void APlayGameMode::BeginPlay()
{
	ARoom* FirstRoom = CreateRoom(0, 0, "Room_01.png");
	FirstRoom->SetName("FirstRoom");

	ARoom* RoomE = CreateRoom(1, 0, "Room_02.png");
	RoomE->SetName("RoomE");

	ARoom* RoomW = CreateRoom(-1, 0, "Room_02.png");
	RoomE->SetName("RoomW");

	ARoom* RoomS = CreateRoom(0, 1, "Room_03.png");
	RoomE->SetName("RoomS");

	ARoom* RoomN = CreateRoom(0, -1, "Room_03.png");
	RoomE->SetName("RoomN");



	FirstRoom->InterLink(RoomE, RoomDir::RIGHT);
	FirstRoom->InterLink(RoomW, RoomDir::LEFT);
	FirstRoom->InterLink(RoomS, RoomDir::DOWN);
	FirstRoom->InterLink(RoomN, RoomDir::UP);

	SetCurRoom(FirstRoom);

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{

	}

}



ARoom* APlayGameMode::CreateRoom(int _X, int _Y, std::string_view _RoomImage)
{

	ARoom* NewRoom = GetWorld()->SpawnActor<ARoom>();
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite(_RoomImage);

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation({ MapScale.X * _X, MapScale.Y * _Y });

	return NewRoom;
}

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
#include <EngineBase/EngineString.h>
#include "Isaac.h"
#include <EngineCore/Level.h>



APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::CreateBossRoomPath()
{
	FVector2D CreateRoomPos = { 0,0 };
	RoomBind.insert({ RoomNumber, CreateRoomPos });

	for (size_t i = 0; i < 4; i++)
	{
        int PosValue = Random.RandomInt(1, 4);

		switch (PosValue)
		{
		case 1:
			CreateRoomPos += {0, -1};
			break;
		case 2:
			CreateRoomPos += {1, 0};
			break;
		case 3:
			CreateRoomPos += {0, 1};
			break;
		case 4:
			CreateRoomPos += {-1, 0};
			break;

		default:
			break;

		}

		
		RoomNumber++;		
		RoomBind.insert({ RoomNumber, CreateRoomPos });

		if (4 == RoomNumber)
		{
			int Distance = abs(CreateRoomPos.iX()) + abs(CreateRoomPos.iY());
			if (4 != Distance)
			{
				CreateRoomPos = { 0,0 };
				RoomNumber = 0;
				RoomBind.clear();
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				i = -1;
			}
		}
	}


}

void APlayGameMode::CreateRestRoomPath(int _RoomNumber)
{
	FVector2D CreateRoomPos = { 0,0 };



	while (IsBind(CreateRoomPos))
	{
		if (CreateRoomPos == RoomBind[3])
		{
			CreateRoomPos = { 0,0 };
		}

		int PosValue = Random.RandomInt(1, 4);

		switch (PosValue)
		{
		case 1:
			CreateRoomPos += {0, -1};
			break;
		case 2:
			CreateRoomPos += {1, 0};
			break;
		case 3:
			CreateRoomPos += {0, 1};
			break;
		case 4:
			CreateRoomPos += {-1, 0};
			break;

		default:
			break;
		}
		if (true == IsBind(CreateRoomPos))
		{
		}
		else {
			if (true == IsAdjacentTwice(CreateRoomPos))
			{
				CreateRoomPos = { 0,0 };
			}
		}
	}


		RoomBind.insert({ _RoomNumber,CreateRoomPos });
	
}

void APlayGameMode::BeginPlay()
{

 AIsaac* Player = GetWorld()->GetPawn<AIsaac>();

	CreateBossRoomPath();
	CreateRestRoomPath(5);
	CreateRestRoomPath(6);
	CreateRestRoomPath(7);

	ARoom* Room0 = CreateRoom("Room0",RoomBind[0]);
	ARoom* Room1 = CreateRoom("Room1", RoomBind[1]);
	ARoom* Room2 = CreateRoom("Room2", RoomBind[2]);
	ARoom* Room3 = CreateRoom("Room3", RoomBind[3]);
	ARoom* Room4 = CreateRoom("Room4", RoomBind[4]);
	ARoom* Room5 = CreateRoom("Room5", RoomBind[5]);
	ARoom* Room6 = CreateRoom("Room6", RoomBind[6]);
	ARoom* Room7 = CreateRoom("Room7", RoomBind[7]);

	CurRoom = Room0;
	PrevRoom = Room1;

	int a = 0;

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{
		FVector2D Value = { -480.0f, 270.0f };
		ARoom* Room = Rooms["Room5"];
		FVector2D Pos = Room->RoomPos + Value;
		GetWorld()->SetCameraPos(Pos);
		
	}




	//if (CurRoom != PrevRoom)
	//{

	//	RoomMoveCameraTime += _DeltaTime * 5;
	//	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//	
	//	PrevRoom = Rooms["Room3"];
	//	FVector2D StartCameraPos = PrevRoom->RoomPos;

	//	CurRoom = Rooms["Room4"];
	//	FVector2D TargetCameraPos = CurRoom->RoomPos;

	//	FVector2D CurCameraPos = FVector2D::LerpClamp(StartCameraPos, TargetCameraPos, RoomMoveCameraTime);
	//	
	//	ULevel NewLevel = ULevel();

	//	NewLevel.SetCameraPos(CurCameraPos);

	//	if (1.0f <= RoomMoveCameraTime)
	//	{
	//		RoomMoveCameraTime = 0.0f;
	//		PrevRoom = CurRoom;
	//		CurRoom->GetWorld()->SetCameraPos(GetActorLocation() - Size.Half());;
	//	}

	//	int a = 0;
	//}

}



ARoom* APlayGameMode::CreateRoom(std::string_view _RoomName,FVector2D _Pos)
{


	ARoom* NewRoom = GetWorld()->SpawnActor<ARoom>();
	NewRoom->SetName(_RoomName);
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);

	
	if ("Room4" == _RoomName)
	{
		SpriteRenderer->SetSprite("Room_03.png");
	}
	else if (("Room5" == _RoomName || "Room6" == _RoomName || "Room7" == _RoomName) )
	{
		SpriteRenderer->SetSprite("Room_02.png");
    }
	else 
	{
		SpriteRenderer->SetSprite("Room_01.png");
	}

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);


	
   
	

	NewRoom->RoomPos = { MapScale.X * _Pos.X, MapScale.Y * _Pos.Y };
	SpriteRenderer->SetComponentLocation(NewRoom->RoomPos);
	Rooms.insert({ _RoomName,NewRoom });
	
	RoomNumber++;

	return NewRoom;
}

#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
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
	int RoomNumber =0;
	FVector2D CreateRoomPos = { 0,0 };
	RoomBind.insert({ RoomNumber, CreateRoomPos });
	int RandomValue = Random.RandomInt(1, 4);

	switch (RandomValue)
	{
	case 1:
		CreateRoomPos += {0, -1};
		RoomNumber++;
		RoomBind.insert({ RoomNumber, CreateRoomPos });
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {0, -1};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;

			case 2:
				CreateRoomPos += {1, 0};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;
			default:
				break;
			}
		}
		break;
	case 2:
		CreateRoomPos += {1, 0};
		RoomNumber++;
		RoomBind.insert({ RoomNumber, CreateRoomPos });
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {1, 0};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;

			case 2:
				CreateRoomPos += {0, 1};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;
			default:
				break;
			}
		}
		break;
	case 3:
		CreateRoomPos += {0, 1};
		RoomNumber++;
		RoomBind.insert({ RoomNumber, CreateRoomPos });
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {0, 1};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;

			case 2:
				CreateRoomPos += {-1, 0};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;
			default:
				break;
			}
		}
		break;
	case 4:
		CreateRoomPos += {-1, 0};
		RoomNumber++;
		RoomBind.insert({ RoomNumber, CreateRoomPos });
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {-1, 0};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;

			case 2:
				CreateRoomPos += {0, -1};
				RoomNumber++;
				RoomBind.insert({ RoomNumber, CreateRoomPos });
				break;
			default:
				break;
			}
		}
		break;

	default:
		break; 
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

	Link(Room0);
	Link(Room1);
	Link(Room2);
	Link(Room3);
	Link(Room4);
	Link(Room5);
	Link(Room6);
	Link(Room7);



	CurRoom = Room0;
	PrevRoom = Room0;
	GetWorld()->SetCameraPos({ CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f });

	int a = 0;

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{	
		int a = 0;
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD0))
	{
		CurRoom = Rooms[0];
		
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD1))
	{
		CurRoom = Rooms[1];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD2))
	{
		CurRoom = Rooms[2];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD3))
	{
		CurRoom = Rooms[3];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD4))
	{
		CurRoom = Rooms[4];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD5))
	{
		CurRoom = Rooms[5];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD6))
	{
		CurRoom = Rooms[6];
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD7))
	{
		CurRoom = Rooms[7];
	}



	
	if (CurRoom != PrevRoom)
	{

		RoomMoveCameraTime += _DeltaTime * 5;
		FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
				
		FVector2D StartCameraPos = { PrevRoom->RoomPos.X - 480.0f ,PrevRoom->RoomPos.Y - 270.0f };

		FVector2D TargetCameraPos = { CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f };

		FVector2D CurCameraPos = FVector2D::LerpClamp(StartCameraPos, TargetCameraPos, RoomMoveCameraTime);
		
	    GetWorld()->SetCameraPos(CurCameraPos);

		if (1.0f <= RoomMoveCameraTime)
		{
			RoomMoveCameraTime = 0.0f;
			PrevRoom = CurRoom;
			GetWorld()->SetCameraPos({ CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f });
			GetWorld()->GetPawn()->SetActorLocation(CurRoom->RoomPos);
		}

		int a = 0;
	}

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


	
   
	
	NewRoom->NomalizedRoomPos = _Pos;
	NewRoom->RoomPos = { MapScale.X * _Pos.X , MapScale.Y * _Pos.Y};
	SpriteRenderer->SetComponentLocation(NewRoom->RoomPos);
	Rooms.insert({ RoomNumber,NewRoom });
	
	RoomNumber++;

	return NewRoom;
}

void APlayGameMode::Link(ARoom* _Room)
{
	FVector2D NewPosUp = { _Room->NomalizedRoomPos.X ,_Room->NomalizedRoomPos.Y - 1 };
	FVector2D NewPosRight = { _Room->NomalizedRoomPos.X + 1 ,_Room->NomalizedRoomPos.Y };
	FVector2D NewPosDown = { _Room->NomalizedRoomPos.X ,_Room->NomalizedRoomPos.Y + 1 };
	FVector2D NewPosLeft = { _Room->NomalizedRoomPos.X - 1 ,_Room->NomalizedRoomPos.Y };

	if (true == IsBind(NewPosUp))
	{
		int Key = Roomkey(NewPosUp);
		_Room->LinkedRooms.insert({ RoomDir::UP,Rooms[Key]});
		_Room->CreateDoor(RoomDir::UP,_Room->RoomPos);
	}
	if (true == IsBind(NewPosRight))
	{
		int Key = Roomkey(NewPosRight);
		_Room->LinkedRooms.insert({ RoomDir::RIGHT,Rooms[Key] });
		_Room->CreateDoor(RoomDir::RIGHT, _Room->RoomPos);
	}
	if (true == IsBind(NewPosDown))
	{
		int Key = Roomkey(NewPosDown);
		_Room->LinkedRooms.insert({ RoomDir::DOWN,Rooms[Key] });
		_Room->CreateDoor(RoomDir::DOWN, _Room->RoomPos);
	}
	if (true == IsBind(NewPosLeft))
	{
		int Key = Roomkey(NewPosLeft);
		_Room->LinkedRooms.insert({ RoomDir::LEFT,Rooms[Key] });
		_Room->CreateDoor(RoomDir::LEFT, _Room->RoomPos);
	}

}


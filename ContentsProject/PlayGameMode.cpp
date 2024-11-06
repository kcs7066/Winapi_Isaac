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
			int Distance = abs(CreateRoomPos.X) + abs(CreateRoomPos.Y);
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
		if (true == IsAdjacentTwice(CreateRoomPos))
		{
			CreateRoomPos = { 0,0 };
		}
	}


		RoomBind.insert({ _RoomNumber,CreateRoomPos });
	
}

void APlayGameMode::BeginPlay()
{
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



	//ARoom* Room5 = CreateRoom("Room5");

	//ARoom* Room6 = CreateRoom("Room6");

	//ARoom* Room7 = CreateRoom("Room7");

	//ARoom* Room8 = CreateRoom("Room8");



	//Room0->InterLink(Room1, RoomDir::LEFT);
	//FirstRoom->InterLink(RoomW, RoomDir::LEFT);
	//FirstRoom->InterLink(RoomS, RoomDir::DOWN);
	//FirstRoom->InterLink(RoomN, RoomDir::UP);

	//SetCurRoom(Room0);
	//bool Value = Room0->IsLink(RoomDir::LEFT);
	//bool Value1 = Room1->IsLink(RoomDir::LEFT);
	
	int a = 0;

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('Q'))
	{

	}

}



ARoom* APlayGameMode::CreateRoom(std::string_view _RoomName,FVector2D _Pos)
{

	//int Value = Random.RandomInt(1,3);



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
		//if(1==Value)
	//{
	//	SpriteRenderer->SetSprite("Room_01.png");
	//}
	//else if (2 == Value)
	//{
	//	SpriteRenderer->SetSprite("Room_02.png");
	//}
	//else
	//{
	//	SpriteRenderer->SetSprite("Room_03.png");
	//}

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(0.1f);


	
   
	

	NewRoom->RoomPos = { MapScale.X * _Pos.X, MapScale.Y * _Pos.Y };
	SpriteRenderer->SetComponentLocation(NewRoom->RoomPos);
	Rooms.insert({ _RoomName,NewRoom });
	
	RoomNumber++;

	return NewRoom;
}

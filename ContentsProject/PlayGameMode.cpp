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
#include "Tear.h"
#include <EngineCore/2DCollision.h>
#include "PurpleFly.h"
#include "RoundWorm.h"
#include "Dip.h"
#include "Spider.h"
#include "BabyLongLegs.h"
#include "LevelTwoSpiderSmall.h"
#include "Fly.h"
#include "RedFly.h"
#include "Monstro.h"
#include "Rock.h"
#include "Poop.h"


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

	CreateRoom("FirstRoom",RoomBind[0]);
	Rooms[0]->CanSpawnNumber = 0;
	CreateRoom("Room1", RoomBind[1]);
	CreateRoom("Room2", RoomBind[2]);
	CreateRoom("Room3", RoomBind[3]);
	CreateRoom("BossRoom", RoomBind[4], RoomType::BOSS);
	CreateRoom("AdditionalRoom1", RoomBind[5]);
	CreateRoom("AdditionalRoom2", RoomBind[6]);
	CreateRoom("GoldRoom", RoomBind[7], RoomType::GOLD);

	Link(Rooms[0]);
	Link(Rooms[1]);
	Link(Rooms[2]);
	Link(Rooms[3]);
	Link(Rooms[4]);
	Link(Rooms[5]);
	Link(Rooms[6]);
	Link(Rooms[7]);



	CurRoom = Rooms[0];
	PrevRoom = Rooms[0];
	GetWorld()->SetCameraPos({ CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f });

	
	


}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('B'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}


	if (true == UEngineInput::GetInst().IsDown('1'))
	{
		ALevelTwoSpiderSmall* Monster = GetWorld()->SpawnActor<ALevelTwoSpiderSmall>();
	}

	if (true == UEngineInput::GetInst().IsDown('2'))
	{
		ABabyLongLegs* Monster = GetWorld()->SpawnActor<ABabyLongLegs>();
	}

	if (true == UEngineInput::GetInst().IsDown('3'))
	{
		ADip* Monster = GetWorld()->SpawnActor<ADip>();
	}

	if (true == UEngineInput::GetInst().IsDown('4'))
	{
		ARoundWorm* Monster = GetWorld()->SpawnActor<ARoundWorm>();
	}

	if (true == UEngineInput::GetInst().IsDown('5'))
	{
		AFly* Monster = GetWorld()->SpawnActor<AFly>();
	}

	if (true == UEngineInput::GetInst().IsDown('6'))
	{
		ARedFly* Monster = GetWorld()->SpawnActor<ARedFly>();
	}

	if (true == UEngineInput::GetInst().IsDown('7'))
	{
		AMonstro* Monster = GetWorld()->SpawnActor<AMonstro>();
	}

	if (true == UEngineInput::GetInst().IsDown('8'))
	{
		ASpider* Monster = GetWorld()->SpawnActor<ASpider>();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_NUMPAD0))
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
		AIsaac* Ptr = GetWorld()->GetPawn<AIsaac>();


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
			//GetWorld()->GetPawn()->SetActorLocation(CurRoom->RoomPos);

			if (nullptr != Ptr)
			{
				Ptr->CanMove = true;
			}
			else {
				int a = 0;
			}

			if (1 == CurRoom->CanSpawnNumber)
			{
				CreateMap();
				CurRoom->RoomClear = false;
				CurRoom->CanSpawnNumber--;

			}
			
		}

		
	
	}

}



void APlayGameMode::CreateRoom(std::string_view _RoomName,FVector2D _Pos, RoomType _Type)
{


	ARoom* NewRoom = GetWorld()->SpawnActor<ARoom>();
	NewRoom->SetName(_RoomName);
	
	
	NewRoom->NomalizedRoomPos = _Pos;
	NewRoom->RoomPos = { 960.0f * _Pos.X , 540.0f * _Pos.Y };
	NewRoom->RoomRenderer->SetComponentLocation(NewRoom->RoomPos);


	Rooms.insert({ RoomNumber,NewRoom });	
	RoomNumber++;

	
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
		_Room->CreateDoor(RoomDir::UP,_Room->RoomPos, Rooms[Key]);
	}
	if (true == IsBind(NewPosRight))
	{
		int Key = Roomkey(NewPosRight);
		_Room->LinkedRooms.insert({ RoomDir::RIGHT,Rooms[Key] });
		_Room->CreateDoor(RoomDir::RIGHT, _Room->RoomPos, Rooms[Key]);
	}
	if (true == IsBind(NewPosDown))
	{
		int Key = Roomkey(NewPosDown);
		_Room->LinkedRooms.insert({ RoomDir::DOWN,Rooms[Key] });
		_Room->CreateDoor(RoomDir::DOWN, _Room->RoomPos, Rooms[Key]);
	}
	if (true == IsBind(NewPosLeft))
	{
		int Key = Roomkey(NewPosLeft);
		_Room->LinkedRooms.insert({ RoomDir::LEFT,Rooms[Key] });
		_Room->CreateDoor(RoomDir::LEFT, _Room->RoomPos, Rooms[Key]);
	}

}

void APlayGameMode::CreateMap()
{
	if (Rooms[4] == CurRoom)
	{
		SetMonster<AMonstro>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
		SetMonster <ARedFly> ({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
		SetMonster<ARedFly>({ CurRoom->RoomPos.X + 52.0f * (-2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
	}
	else
	{
		int RandomValue = Random.RandomInt(1, 4);
		switch (RandomValue)
		{
		case 1:
			SetMonster<ARoundWorm>({ CurRoom->RoomPos.X + 52.0f * (-6.0f), CurRoom->RoomPos.Y - 52.0f * (3.0f) });
			SetMonster<ARoundWorm>({ CurRoom->RoomPos.X + 52.0f * (6.0f), CurRoom->RoomPos.Y - 52.0f * (-3.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-6.0f), CurRoom->RoomPos.Y - 52.0f * (-3.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-6.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-5.0f), CurRoom->RoomPos.Y - 52.0f * (-3.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (6.0f), CurRoom->RoomPos.Y - 52.0f * (3.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (6.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (5.0f), CurRoom->RoomPos.Y - 52.0f * (3.0f) });
			break;
		case 2:
			SetMonster<ADip>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetMonster<ADip>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetMonster<ADip>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<ADip>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });

			break;

		case 3:
			SetMonster<ALevelTwoSpiderSmall>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;

		case 4:
			SetMonster<AFly>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;

		case 5:
			SetMonster<ABabyLongLegs>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;


		default:
			break;
		}
	}
}
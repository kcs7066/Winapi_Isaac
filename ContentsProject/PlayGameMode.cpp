#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/SpriteRenderer.h>

#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/Level.h>

#include "TitleGameMode.h"
#include "ContentsEnum.h"
#include "Isaac.h"

#include "RoundWorm.h"
#include "Dip.h"
#include "Spider.h"
#include "BabyLongLegs.h"
#include "LevelTwoSpiderSmall.h"
#include "RedFly.h"
#include "Gaper.h"
#include "Pacer.h"
#include "Fatty.h"
#include "Pooter.h"
#include "Monstro.h"
#include "Larryjr.h"
#include "Rock.h"
#include "Poop.h"
#include "PickUpBomb.h"
#include "PickUpHeart.h"
#include "TheInnerEye.h"
#include "Fade.h"




APlayGameMode::APlayGameMode()
{
	MapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MapRenderer->SetCameraEffect(false);
	MapRenderer->SetOrder(ERenderOrder::MAPBOARD);
	MapRenderer->SetSprite("Minimap1.png");
	MapRenderer->SetSpriteScale(3.0f);
	MapRenderer->SetComponentLocation({850,80});

	BossMiniMapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BossMiniMapRenderer->SetCameraEffect(false);
	BossMiniMapRenderer->SetOrder(ERenderOrder::ICON);
	BossMiniMapRenderer->SetComponentScale({ 30,30 });
	BossMiniMapRenderer->CreateAnimation("Boss", "Minimap_Icons.png", 9, 9, 0.1f);	
	BossMiniMapRenderer->ChangeAnimation("Boss");
	

	GoldMiniMapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	GoldMiniMapRenderer->SetCameraEffect(false);
	GoldMiniMapRenderer->SetOrder(ERenderOrder::ICON);
	GoldMiniMapRenderer->SetComponentScale({ 30,30 });
	GoldMiniMapRenderer->CreateAnimation("Gold", "Minimap_Icons.png", 4, 4, 0.1f);
	GoldMiniMapRenderer->ChangeAnimation("Gold");

	PauseGameRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PauseGameRenderer->SetOrder(ERenderOrder::MENU);
	PauseGameRenderer->SetSprite("PauseGame.png");
	PauseGameRenderer->SetSpriteScale(0.0f);
	PauseGameRenderer->SetComponentLocation({ 0,0 });
	
	RestartGameRenderer = CreateDefaultSubObject<USpriteRenderer>();
	RestartGameRenderer->SetOrder(ERenderOrder::MENU);
	RestartGameRenderer->SetSprite("Die.png");
	RestartGameRenderer->SetSpriteScale(0.0f);
	RestartGameRenderer->SetComponentLocation({ 0,0 });

	
}

APlayGameMode::~APlayGameMode()
{

}



void APlayGameMode::BeginPlay()
{
UEngineAPICore::GetCore()->DestroyLevel("Title");
	
Fade = GetWorld()->SpawnActor<AFade>();
Fade->FadeOut();
	

 AIsaac* Player = GetWorld()->GetPawn<AIsaac>();

	CreateBossRoomPath();
	CreateRestRoomPath(5);
	CreateRestRoomPath(6);
	CreateRestRoomPath(7);

	CreateRoom("FirstRoom",NormalizedRoom[0]);
	Rooms[0]->CanSpawnNumber = 0;
	CreateRoom("Room1", NormalizedRoom[1]);
	CreateRoom("Room2", NormalizedRoom[2]);
	CreateRoom("Room3", NormalizedRoom[3]);
	CreateRoom("BossRoom", NormalizedRoom[4], RoomType::BOSS);
	CreateRoom("AdditionalRoom1", NormalizedRoom[5]);
	CreateRoom("AdditionalRoom2", NormalizedRoom[6]);
	CreateRoom("GoldRoom", NormalizedRoom[7], RoomType::GOLD);

	Rooms[0]->MiniMapRenderer->ChangeAnimation("Now");
	Rooms[0]->RoomRenderer->SetSprite("FirstRoom.png");
	Rooms[4]->RoomRenderer->SetSprite("Room_03.png");

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

	BombUi = GetWorld()->SpawnActor<AUi>();
	BombUi->SetActorLocation({ 80, 130 });
	BombUi->SetTextSpriteName("Number.png");
	BombUi->SetOrder(ERenderOrder::UI);
	BombUi->SetTextScale({ 30, 30 });
	BombUi->SetValue(1);
	BombUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BombUi->HUDRenderer->SetCameraEffect(false);
	BombUi->HUDRenderer->SetOrder(ERenderOrder::UI);
	BombUi->HUDRenderer->SetComponentScale({ 30, 30 });
	BombUi->HUDRenderer->SetComponentLocation({ 50, 127 });
	BombUi->HUDRenderer->CreateAnimation("HUD_Bomb", "HUDPickups.png", 8, 8, 0.1f);
	BombUi->HUDRenderer->ChangeAnimation("HUD_Bomb");

	HeartUi = GetWorld()->SpawnActor<AUi>();
	HeartUi->SetActorLocation({ 120, -120 });
	HeartUi->SetTextSpriteName("Number.png");
	HeartUi->SetOrder(ERenderOrder::UI);

	HeartUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();
	HeartUi->HUDRenderer->SetCameraEffect(false);
	HeartUi->HUDRenderer->SetOrder(ERenderOrder::UI);
	HeartUi->HUDRenderer->SetComponentScale({ 30, 30 });
	HeartUi->HUDRenderer->SetComponentLocation({ 120, 45 });
	HeartUi->HUDRenderer->CreateAnimation("Full_Heart", "Ui_Hearts.png", 0, 0, 0.1f);
	HeartUi->HUDRenderer->CreateAnimation("Half_Heart", "Ui_Hearts.png", 1, 1, 0.1f);
	HeartUi->HUDRenderer->CreateAnimation("Empty_Heart", "Ui_Hearts.png", 2, 2, 0.1f);
	HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");

	SecondHeartUi = GetWorld()->SpawnActor<AUi>();
	SecondHeartUi->SetActorLocation({ 120, -120 });
	SecondHeartUi->SetTextSpriteName("Number.png");
	SecondHeartUi->SetOrder(ERenderOrder::UI);

	SecondHeartUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SecondHeartUi->HUDRenderer->SetCameraEffect(false);
	SecondHeartUi->HUDRenderer->SetOrder(ERenderOrder::UI);
	SecondHeartUi->HUDRenderer->SetComponentScale({ 30, 30 });
	SecondHeartUi->HUDRenderer->SetComponentLocation({ 145, 45 });
	SecondHeartUi->HUDRenderer->CreateAnimation("Full_Heart", "Ui_Hearts.png", 0, 0, 0.1f);
	SecondHeartUi->HUDRenderer->CreateAnimation("Half_Heart", "Ui_Hearts.png", 1, 1, 0.1f);
	SecondHeartUi->HUDRenderer->CreateAnimation("Empty_Heart", "Ui_Hearts.png", 2, 2, 0.1f);
	SecondHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");

	ThirdHeartUi = GetWorld()->SpawnActor<AUi>();
	ThirdHeartUi->SetActorLocation({ 120, -120 });
	ThirdHeartUi->SetTextSpriteName("Number.png");
	ThirdHeartUi->SetOrder(ERenderOrder::UI);

	ThirdHeartUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ThirdHeartUi->HUDRenderer->SetCameraEffect(false);
	ThirdHeartUi->HUDRenderer->SetOrder(ERenderOrder::UI);
	ThirdHeartUi->HUDRenderer->SetComponentScale({ 30, 30 });
	ThirdHeartUi->HUDRenderer->SetComponentLocation({ 170, 45 });
	ThirdHeartUi->HUDRenderer->CreateAnimation("Full_Heart", "Ui_Hearts.png", 0, 0, 0.1f);
	ThirdHeartUi->HUDRenderer->CreateAnimation("Half_Heart", "Ui_Hearts.png", 1, 1, 0.1f);
	ThirdHeartUi->HUDRenderer->CreateAnimation("Empty_Heart", "Ui_Hearts.png", 2, 2, 0.1f);
	ThirdHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");


	BGMPlayer = UEngineSound::Play("diptera sonata.ogg");
	BGMPlayer.Loop(100);

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("Room : " + APlayGameMode::CurRoom->GetName());

	if (true == UEngineInput::GetInst().IsDown('B'))
	{
		UEngineDebug::SwitchIsDebug();
	}
	
	if (true == DeathValue)
	{
		RestartGameRenderer->SetComponentLocation(CurRoom->RoomPos);
		RestartGameRenderer->SetSpriteScale(1.0f);
		UEngineAPICore::GetCore()->SetGlobalTimeScale(0.0f);
		Fade->BackSpriteRenderer->SetAlphafloat(0.8f);
	}

	if (true == UEngineInput::GetInst().IsDown(VK_ESCAPE))
	{

		if (false == PauseGame)
		{
			if (true == DeathValue)
			{
				BGMPlayer.Off();
				UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
				UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
				UEngineAPICore::GetCore()->OpenLevel("Title");
			}
			else
			{
				PauseGameRenderer->SetComponentLocation(CurRoom->RoomPos);
				PauseGameRenderer->SetSpriteScale(1.0f);
				UEngineAPICore::GetCore()->SetGlobalTimeScale(0.0f);
				Fade->BackSpriteRenderer->SetAlphafloat(0.8f);
				EffectPlayer = UEngineSound::Play("paper_in.wav");
				PauseGame = true;
			}
		}
	
	}

	if (true == UEngineInput::GetInst().IsDown(VK_DOWN)||
		true == UEngineInput::GetInst().IsDown(VK_UP)
		)
	{
		if (true == PauseGame && false == ExitGameValue)
		{
			PauseGameRenderer->SetSprite("ExitGame.png");
			ExitGameValue = true;
		}
        else if (true == PauseGame && true == ExitGameValue)
		{
			PauseGameRenderer->SetSprite("PauseGame.png");
			ExitGameValue = false;
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		if (true == ExitGameValue)
		{
	    BGMPlayer.Off();
		PauseGameRenderer->SetSpriteScale(0.0f);
		UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
		Fade->BackSpriteRenderer->SetAlphafloat(0.00f);
		PauseGame = false;
		UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
        UEngineAPICore::GetCore()->OpenLevel("Title");
		}
		else if (true == PauseGame)
		{
			PauseGameRenderer->SetSpriteScale(0.0f);
			UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
			Fade->BackSpriteRenderer->SetAlphafloat(0.00f);
			PauseGame = false;
			EffectPlayer = UEngineSound::Play("paper_out.wav");
		}


		if (true == DeathValue)
		{
			UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
			BGMPlayer.Off();
		UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AIsaac>("Play");
		DeathValue = false;
		}
	}


	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		BGMPlayer.Off();
	UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AIsaac>("Play");
	}



	if (CurRoom != PrevRoom)
	{
		AIsaac* Ptr = GetWorld()->GetPawn<AIsaac>();


		RoomMoveCameraTime += _DeltaTime * 5;
		FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();		
		FVector2D StartCameraPos = { PrevRoom->RoomPos.X - 480.0f ,PrevRoom->RoomPos.Y - 270.0f };
		FVector2D TargetCameraPos = { CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f };
		FVector2D CurCameraPos = FVector2D::MyLerpClamp(StartCameraPos, TargetCameraPos, RoomMoveCameraTime);
		
	    GetWorld()->SetCameraPos(CurCameraPos);

		if (1.0f <= RoomMoveCameraTime)
		{
			RoomMoveCameraTime = 0.0f;
			PrevRoom->MiniMapRenderer->ChangeAnimation("Clear");

			PrevRoom = CurRoom;

			GetWorld()->SetCameraPos({ CurRoom->RoomPos.X - 480.0f ,CurRoom->RoomPos.Y - 270.0f });

			if (nullptr != Ptr)
			{
				Ptr->CanMove = true;
			}
			else {
			}

			if (1 == CurRoom->CanSpawnNumber)
			{
				if (RoomType::GOLD == CurRoom->Type)
				{
					CreateItem();
					CurRoom->CanSpawnNumber--;
				}

				else
				{
					CreateMap();
					CurRoom->RoomClear = false;
					CurRoom->RewardValue = true;
					CurRoom->CanSpawnNumber--;
				}

			}
			CurRoom->MiniMapRenderer->ChangeAnimation("Now");
		}
	}
}

void APlayGameMode::CreateBossRoomPath()
{
	int RoomNumber = 0;
	FVector2D CreateRoomPos = { 0,0 };
	NormalizedRoom.push_back(CreateRoomPos);
	int RandomValue = Random.RandomInt(1, 4);

	switch (RandomValue)
	{
	case 1:
		CreateRoomPos += {0, -1};
		RoomNumber++;
		NormalizedRoom.push_back(CreateRoomPos);
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {0, -1};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;

			case 2:
				CreateRoomPos += {1, 0};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;
			default:
				break;
			}
		}
		break;
	case 2:
		CreateRoomPos += {1, 0};
		RoomNumber++;
		NormalizedRoom.push_back(CreateRoomPos);
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {1, 0};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;

			case 2:
				CreateRoomPos += {0, 1};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;
			default:
				break;
			}
		}
		break;
	case 3:
		CreateRoomPos += {0, 1};
		RoomNumber++;
		NormalizedRoom.push_back(CreateRoomPos);
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {0, 1};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;

			case 2:
				CreateRoomPos += {-1, 0};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;
			default:
				break;
			}
		}
		break;
	case 4:
		CreateRoomPos += {-1, 0};
		RoomNumber++;
		NormalizedRoom.push_back(CreateRoomPos);
		for (size_t i = 0; i < 3; i++)
		{
			RandomValue = Random.RandomInt(1, 2);

			switch (RandomValue)
			{

			case 1:
				CreateRoomPos += {-1, 0};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
				break;

			case 2:
				CreateRoomPos += {0, -1};
				RoomNumber++;
				NormalizedRoom.push_back(CreateRoomPos);
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

bool APlayGameMode::IsBind(FVector2D _Pos)
{
	{
		std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
		std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == _Pos)
			{
				return true;
			}
		}
	}
	return false;
}

bool APlayGameMode::IsAdjacentTwice(FVector2D _Pos)
{
	int AdjacentRoom = 0;
	FVector2D AdjacentPos1 = { _Pos.X + 1 , _Pos.Y };
	FVector2D AdjacentPos2 = { _Pos.X - 1 , _Pos.Y };
	FVector2D AdjacentPos3 = { _Pos.X , _Pos.Y + 1 };
	FVector2D AdjacentPos4 = { _Pos.X , _Pos.Y - 1 };

	{
		std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
		std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == AdjacentPos1)
				AdjacentRoom++;
		}
	}

	{
		std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
		std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == AdjacentPos2)
				AdjacentRoom++;
		}
	}
	{
		std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
		std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == AdjacentPos3)
				AdjacentRoom++;
		}
	}
	{
		std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
		std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == AdjacentPos4)
				AdjacentRoom++;
		}
	}

	if (AdjacentRoom == 1)
	{
		return false;
	}
	return true;
}

int APlayGameMode::Roomkey(FVector2D _Pos)
{
	std::vector<FVector2D>::iterator StartIter = NormalizedRoom.begin();
	std::vector<FVector2D>::iterator EndIter = NormalizedRoom.end();

	for (int index = 0; StartIter != EndIter; ++StartIter, ++index)
	{
		if (*StartIter == _Pos)
			return index;
	}
	return 0;
}

void APlayGameMode::CreateRestRoomPath(int _RoomNumber)
{
	FVector2D CreateRoomPos = { 0,0 };



	while (IsBind(CreateRoomPos))
	{
		if (CreateRoomPos == NormalizedRoom[3])
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


	NormalizedRoom.push_back(CreateRoomPos);

}

void APlayGameMode::CreateRoom(std::string_view _RoomName,FVector2D _Pos, RoomType _Type)
{


	ARoom* NewRoom = GetWorld()->SpawnActor<ARoom>();
	NewRoom->SetName(_RoomName);
	
	
	NewRoom->NomalizedRoomPos = _Pos;
	NewRoom->MiniMapRenderer->SetComponentLocation({ 850.0f + (_Pos.X * 16.2f) , 80.0f + (_Pos.Y * 14.4f) });
	if (RoomType::GOLD == _Type)
	{
		GoldMiniMapRenderer->SetComponentLocation({ 854.0f + (_Pos.X * 16.2f) , 84.0f + (_Pos.Y * 14.4f) });
	}
	else if (RoomType::BOSS == _Type)
	{
		BossMiniMapRenderer->SetComponentLocation({ 854.0f + (_Pos.X * 16.2f) , 84.0f + (_Pos.Y * 14.4f) });
	}
	NewRoom->RoomPos = { 960.0f * _Pos.X , 540.0f * _Pos.Y };
	NewRoom->RoomRenderer->SetComponentLocation(NewRoom->RoomPos);
	NewRoom->Type = _Type;
	NewRoom->Random.SetSeed(time(nullptr) + SeedValue);
	SeedValue++;

	Rooms.push_back({NewRoom});	

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

void APlayGameMode::CreateItem()
{
	ATheInnerEye* Item = GetWorld()->SpawnActor<ATheInnerEye>();
	Item->SetActorLocation(CurRoom->RoomPos);
}

void APlayGameMode::CreateMap()
{
	
	if (Rooms[4] == CurRoom)
	{
		int RandomValue = Random.RandomInt(2, 2);

		switch (RandomValue)
		{
		case 1:
			SetMonster<AMonstro>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster <ARedFly>({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<ARedFly>({ CurRoom->RoomPos.X + 52.0f * (-2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;
		case 2:
			Monster0 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (3.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			Monster0->MonsterRenderer->SetComponentLocation({ 0,-25 });
			Monster0 -> ShadowRenderer->SetSpriteScale(0.5f);
			Monster0->Part = LarryjrPart::HEAD;
			Monster1 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			Monster1->Part = LarryjrPart::BODY;
			Monster2 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			Monster2->Part = LarryjrPart::BODY;
			Monster3 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			Monster3->Part = LarryjrPart::TAIL;

			Monster0->LinkedParts[LinkDir::Back] = Monster1;
			Monster1->LinkedParts[LinkDir::Front] = Monster0;
			Monster1->LinkedParts[LinkDir::Back] = Monster2;
			Monster2->LinkedParts[LinkDir::Front] = Monster1;
			Monster2->LinkedParts[LinkDir::Back] = Monster3;
			Monster3->LinkedParts[LinkDir::Front] = Monster2;

			Monster4 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			Monster4->MonsterRenderer->SetComponentLocation({ 0,-25 });
			Monster4->ShadowRenderer->SetSpriteScale(0.5f);
			Monster4->Part = LarryjrPart::HEAD;
			Monster5 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			Monster5->Part = LarryjrPart::BODY;
			Monster6 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (-2.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			Monster6->Part = LarryjrPart::BODY;
			Monster7 = SetMonster<ALarryjr>({ CurRoom->RoomPos.X + 52.0f * (-3.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			Monster7->Part = LarryjrPart::TAIL;

			Monster4->LinkedParts[LinkDir::Back] = Monster5;
			Monster5->LinkedParts[LinkDir::Front] = Monster4;
			Monster5->LinkedParts[LinkDir::Back] = Monster6;
			Monster6->LinkedParts[LinkDir::Front] = Monster5;
			Monster6->LinkedParts[LinkDir::Back] = Monster7;
			Monster7->LinkedParts[LinkDir::Front] = Monster6;

			break;
		default:
			break;
		}
		EffectPlayer = UEngineSound::Play("castleportcullis.wav");
	}
	else
	{
		switch (SpawnCaseValue)
		{

		case 1:
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


		case 2:
			SetMonster<APooter>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<APooter>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetMonster<APooter>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetMonster<APooter>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetMonster<APooter>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<APoop>({ CurRoom->RoomPos.X + 52.0f * (-2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;

		case 3:
		
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

	    case 4:
			SetMonster<AFatty>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<AGaper>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<AGaper>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<APacer>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetMonster<APacer>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f)});
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f)});
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (3.0f), CurRoom->RoomPos.Y - 52.0f * (2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (3.0f), CurRoom->RoomPos.Y - 52.0f * (1.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (3.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-3.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-3.0f), CurRoom->RoomPos.Y - 52.0f * (-1.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-3.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (- 2.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f)});
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (-1.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f) });
			SetStructure<ARock>({ CurRoom->RoomPos.X + 52.0f * (1.0f), CurRoom->RoomPos.Y - 52.0f * (-2.0f) });

			break;

		case 5:
			SetMonster<ABabyLongLegs>({ CurRoom->RoomPos.X + 52.0f * (0.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<ALevelTwoSpiderSmall>({ CurRoom->RoomPos.X + 52.0f * (2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			SetMonster<ALevelTwoSpiderSmall>({ CurRoom->RoomPos.X + 52.0f * (-2.0f), CurRoom->RoomPos.Y - 52.0f * (0.0f) });
			break;

		default:
			break;
		}
		SpawnCaseValue++;
	}
}
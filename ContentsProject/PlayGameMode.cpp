#include "PreCompile.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
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
#include "Larryjr.h"
#include "PickUpBomb.h"
#include "PickUpCoin.h"
#include "PickUpKey.h"
#include "PickUpHeart.h"
#include "TheInnerEye.h"
#include "Gaper.h"
#include "Pacer.h"
#include "Fatty.h"
#include "Pooter.h"



APlayGameMode::APlayGameMode()
{
	MapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MapRenderer->SetCameraEffect(false);
	MapRenderer->SetOrder(ERenderOrder::MAPBOARD);
	MapRenderer->SetSprite("Minimap1.png");
	MapRenderer->SetSpriteScale(2.0f);
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

	CreateRoom("FirstRoom",RoomBind[0]);
	Rooms[0]->CanSpawnNumber = 0;
	CreateRoom("Room1", RoomBind[1]);
	CreateRoom("Room2", RoomBind[2]);
	CreateRoom("Room3", RoomBind[3]);
	CreateRoom("BossRoom", RoomBind[4], RoomType::BOSS);
	CreateRoom("AdditionalRoom1", RoomBind[5]);
	CreateRoom("AdditionalRoom2", RoomBind[6]);
	CreateRoom("GoldRoom", RoomBind[7], RoomType::GOLD);

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

	{
	CoinUi = GetWorld()->SpawnActor<AUi>();
	CoinUi->SetActorLocation({80, 105});
	CoinUi->SetTextSpriteName("Number.png");
	CoinUi->SetOrder(ERenderOrder::UI);
	CoinUi->SetTextScale({30, 30});
	CoinUi->SetValue(0);
	CoinUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();	
	CoinUi->HUDRenderer->SetCameraEffect(false);
	CoinUi->HUDRenderer->SetOrder(ERenderOrder::UI);
	CoinUi->HUDRenderer->SetComponentScale({ 30, 30 });
	CoinUi->HUDRenderer->SetComponentLocation({ 50, 102 });
	CoinUi->HUDRenderer->CreateAnimation("HUD_Coin", "HUDPickups.png", 0, 0, 0.1f);
	CoinUi->HUDRenderer->ChangeAnimation("HUD_Coin");

    }
	{
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
	}
	{
		KeyUi = GetWorld()->SpawnActor<AUi>();
		KeyUi->SetActorLocation({ 80, 155 });
		KeyUi->SetTextSpriteName("Number.png");
		KeyUi->SetOrder(ERenderOrder::UI);
		KeyUi->SetTextScale({ 30, 30 });
		KeyUi->SetValue(0);
		KeyUi->HUDRenderer = CreateDefaultSubObject<USpriteRenderer>();
		KeyUi->HUDRenderer->SetCameraEffect(false);
		KeyUi->HUDRenderer->SetOrder(ERenderOrder::UI);
		KeyUi->HUDRenderer->SetComponentScale({ 30, 30 });
		KeyUi->HUDRenderer->SetComponentLocation({ 50, 152 });
		KeyUi->HUDRenderer->CreateAnimation("HUD_Key", "HUDPickups.png", 1, 1, 0.1f);
		KeyUi->HUDRenderer->ChangeAnimation("HUD_Key");
	}

	{
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
	}
	{
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
	}
	{
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
	}
	
	BGMPlayer = UEngineSound::Play("diptera sonata.ogg");
	



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
				BGMPlayer.Off();
				PauseGameRenderer->SetComponentLocation(CurRoom->RoomPos);
				PauseGameRenderer->SetSpriteScale(1.0f);
				UEngineAPICore::GetCore()->SetGlobalTimeScale(0.0f);
				Fade->BackSpriteRenderer->SetAlphafloat(0.8f);
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
		if(false == PauseGame)
		BGMPlayer.On();
		PauseGameRenderer->SetSpriteScale(0.0f);
		UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
		Fade->BackSpriteRenderer->SetAlphafloat(0.00f);
		PauseGame = false;

		if (true == ExitGameValue)
		{
	    BGMPlayer.Off();
		UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
        UEngineAPICore::GetCore()->OpenLevel("Title");
		}


		if (true == DeathValue)
		{
			UEngineAPICore::GetCore()->SetGlobalTimeScale(1.0f);
		UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AIsaac>("Play");
		DeathValue = false;
		}
	}


	if (true == UEngineInput::GetInst().IsDown('R'))
	{
	UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, AIsaac>("Play");
	}


	if (true == UEngineInput::GetInst().IsDown('1'))
	{
		APacer* Monster = GetWorld()->SpawnActor<APacer>();
	}

	if (true == UEngineInput::GetInst().IsDown('2'))
	{
		AFatty* Monster = GetWorld()->SpawnActor<AFatty>();
	}

	if (true == UEngineInput::GetInst().IsDown('3'))
	{
		APooter* Monster = GetWorld()->SpawnActor<APooter>();
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

	if (true == UEngineInput::GetInst().IsDown('9'))
	{
		ALarryjr* Monster = GetWorld()->SpawnActor<ALarryjr>();
	}

	if (true == UEngineInput::GetInst().IsDown('0'))
	{
		AGaper* Monster = GetWorld()->SpawnActor<AGaper>();
	}

	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD1))
	{
		APickUpBomb* Bomb = GetWorld()->SpawnActor<APickUpBomb>();
	}
	
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD2))
	{
		APickUpCoin* Coin = GetWorld()->SpawnActor<APickUpCoin>();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD3))
	{
		APickUpKey* Key = GetWorld()->SpawnActor<APickUpKey>();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD4))
	{
		APickUpHeart* Heart = GetWorld()->SpawnActor<APickUpHeart>();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_NUMPAD5))
	{
		ATheInnerEye* Item = GetWorld()->SpawnActor<ATheInnerEye>();
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

		FVector2D CurCameraPos = FVector2D::MyLerpClamp(StartCameraPos, TargetCameraPos, RoomMoveCameraTime);
		
	    GetWorld()->SetCameraPos(CurCameraPos);

		if (1.0f <= RoomMoveCameraTime)
		{
			RoomMoveCameraTime = 0.0f;
			PrevRoom->MiniMapRenderer->ChangeAnimation("Clear");

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

void APlayGameMode::CreateItem()
{
	ATheInnerEye* Item = GetWorld()->SpawnActor<ATheInnerEye>();
	Item->SetActorLocation(CurRoom->RoomPos);
}

void APlayGameMode::CreateMap()
{
	
	if (Rooms[4] == CurRoom)
	{
		int RandomValue = Random.RandomInt(1, 1);

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
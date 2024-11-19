#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include "PlayGameMode.h"
#include "ContentsEnum.h"
#include <EngineCore/2DCollision.h>

ARoom::ARoom()
{

	RoomRenderer = CreateDefaultSubObject<USpriteRenderer>();
	RoomRenderer->SetOrder(ERenderOrder::BACKGROUND);
	RoomRenderer->SetSprite("Room_01.png");
    RoomRenderer->SetSpriteScale(1.0f);

	MiniMapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MiniMapRenderer->SetCameraEffect(false);
	MiniMapRenderer->SetOrder(ERenderOrder::UI);
	MiniMapRenderer->SetComponentScale({30,30});
	MiniMapRenderer->CreateAnimation("Clear", "Minimap2.png", 0, 0, 0.1f);
	MiniMapRenderer->CreateAnimation("Now", "Minimap2.png", 1, 1, 0.1f);
	MiniMapRenderer->CreateAnimation("Dark", "Minimap2.png", 2, 2, 0.1f);
	MiniMapRenderer->ChangeAnimation("Dark");
}

ARoom::~ARoom()
{
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();
}
void ARoom::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (0==MonsterNumber)
	{
		std::map<RoomDir, ADoor*>::iterator StartIter = Doors.begin();
		std::map<RoomDir, ADoor*>::iterator EndIter = Doors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second->DoorOpen();
		}
		RoomClear = true;
	}

	else
	{
		std::map<RoomDir, ADoor*>::iterator StartIter = Doors.begin();
		std::map<RoomDir, ADoor*>::iterator EndIter = Doors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second->DoorClose();
		}
		RoomClear = false;
	}

}

void ARoom::CreateDoor(RoomDir _Dir, FVector2D _Pos, ARoom* _LinkRoom)
{
	ADoor* NewDoor = GetWorld()->SpawnActor<ADoor>();
	NewDoor->LinkedRoom = _LinkRoom;

	switch (_Dir)
	{
	case RoomDir::NONE:
		break;
	case RoomDir::UP:

		if (RoomType::BOSS == this->Type || RoomType::BOSS == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("UpBossRoomDoor_Close", "BossRoomDoor.png", 6, 6, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("UpBossRoomDoor_Close");
			NewDoor->Type = DoorType::BOSS;
		}
		else if (RoomType::GOLD == this->Type || RoomType::GOLD == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("UpGoldRoomDoor_Close", "GoldRoomDoor.png", 6, 6, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("UpGoldRoomDoor_Close");
			NewDoor->Type = DoorType::GOLD;
		}
		else
		{
			NewDoor->DoorRenderer->CreateAnimation("UpNormalRoomDoor_Close", "NormalRoomDoor.png", 6, 6, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Close");
		}
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y - 215.0f });
		NewDoor->Dir = DoorDir::UP;

		break;
	case RoomDir::RIGHT:

		if (RoomType::BOSS == this->Type || RoomType::BOSS == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("RightBossRoomDoor_Close", "BossRoomDoor.png", 5, 5, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("RightBossRoomDoor_Close");
			NewDoor->Type = DoorType::BOSS;
		}
		else if (RoomType::GOLD == this->Type || RoomType::GOLD == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("RightGoldRoomDoor_Close", "GoldRoomDoor.png", 5, 5, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("RightGoldRoomDoor_Close");
			NewDoor->Type = DoorType::GOLD;

		}
		else
		{
			NewDoor->DoorRenderer->CreateAnimation("RightNormalRoomDoor_Close", "NormalRoomDoor.png", 5, 5, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Close");
		}
		NewDoor->SetActorLocation({ _Pos.X + 370.0f, _Pos.Y });
		NewDoor->Dir = DoorDir::RIGHT;

		break;
	case RoomDir::DOWN:

		if (RoomType::BOSS == this->Type || RoomType::BOSS == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("DownBossRoomDoor_Close", "BossRoomDoor.png", 7, 7, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("DownBossRoomDoor_Close");
			NewDoor->Type = DoorType::BOSS;
		}
		else if (RoomType::GOLD == this->Type || RoomType::GOLD == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("DownGoldRoomDoor_Close", "GoldRoomDoor.png", 7, 7, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("DownGoldRoomDoor_Close");
			NewDoor->Type = DoorType::GOLD;

		}
		else
		{
			NewDoor->DoorRenderer->CreateAnimation("DownNormalRoomDoor_Close", "NormalRoomDoor.png", 7, 7, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Close");
		}
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y + 215.0f });
		NewDoor->Dir = DoorDir::DOWN;

		break;
	case RoomDir::LEFT:

		if (RoomType::BOSS == this->Type || RoomType::BOSS == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("LeftBossRoomDoor_Close", "BossRoomDoor.png", 4, 4, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("LeftBossRoomDoor_Close");
			NewDoor->Type = DoorType::BOSS;
		}
		else if (RoomType::GOLD == this->Type || RoomType::GOLD == NewDoor->LinkedRoom->Type)
		{
			NewDoor->DoorRenderer->CreateAnimation("LeftGoldRoomDoor_Close", "GoldRoomDoor.png", 4, 4, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("LeftGoldRoomDoor_Close");
			NewDoor->Type = DoorType::GOLD;

		}
		else
		{
			NewDoor->DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Close", "NormalRoomDoor.png", 4, 4, 0.1f);
			NewDoor->DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Close");
		}
		NewDoor->SetActorLocation({ _Pos.X - 370.0f, _Pos.Y });
		NewDoor->Dir = DoorDir::LEFT;

		break;
	default:
		break;
	}

	

	//U2DCollision* CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	//CollisionComponent->SetComponentLocation(NewDoor->GetActorLocation());
	//CollisionComponent->SetComponentScale({ 50, 70 });
	//CollisionComponent->SetCollisionGroup(ECollisionGroup::Door);
	//CollisionComponent->SetCollisionType(ECollisionType::Rect);

	
	Doors.insert({ _Dir,NewDoor });
}

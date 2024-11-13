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

	switch (_Dir)
	{
	case RoomDir::NONE:
		break;
	case RoomDir::UP:
		NewDoor->DoorRenderer->CreateAnimation("UpNormalRoomDoor_Close", "NormalRoomDoor.png", 6, 6, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Close");
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y - 215.0f });
		NewDoor->Dir = DoorDir::UP;

		break;
	case RoomDir::RIGHT:
		NewDoor->DoorRenderer->CreateAnimation("RightNormalRoomDoor_Close", "NormalRoomDoor.png", 5, 5, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Close");
		NewDoor->SetActorLocation({ _Pos.X + 370.0f, _Pos.Y });
		NewDoor->Dir = DoorDir::RIGHT;

		break;
	case RoomDir::DOWN:
		NewDoor->DoorRenderer->CreateAnimation("DownNormalRoomDoor_Close", "NormalRoomDoor.png", 7, 7, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Close");
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y + 215.0f });
		NewDoor->Dir = DoorDir::DOWN;

		break;
	case RoomDir::LEFT:
		NewDoor->DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Close", "NormalRoomDoor.png", 4, 4, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Close");
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

	

	NewDoor->LinkedRoom = _LinkRoom;
	Doors.insert({ _Dir,NewDoor });
}

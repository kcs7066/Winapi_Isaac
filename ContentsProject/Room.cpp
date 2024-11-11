#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "PlayGameMode.h"
#include "ContentsEnum.h"
#include <EngineCore/2DCollision.h>

ARoom::ARoom()
{
	
	
	

}

ARoom::~ARoom()
{
}

void ARoom::CreateDoor(RoomDir _Dir, FVector2D _Pos, ARoom* _LinkRoom)
{
	ADoor* NewDoor = GetWorld()->SpawnActor<ADoor>();

	

	switch (_Dir)
	{
	case RoomDir::NONE:
		break;
	case RoomDir::UP:
		NewDoor->DoorRenderer->CreateAnimation("UpNormalRoomDoor_Idle", "NormalRoomDoor.png", 2, 2, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("UpNormalRoomDoor_Idle");
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y - 215.0f });
		NewDoor->DoorRenderer->SetComponentLocation({ _Pos.X, _Pos.Y - 215.0f });


		break;
	case RoomDir::RIGHT:
		NewDoor->DoorRenderer->CreateAnimation("RightNormalRoomDoor_Idle", "NormalRoomDoor.png", 1, 1, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("RightNormalRoomDoor_Idle");
		NewDoor->SetActorLocation({ _Pos.X + 370.0f, _Pos.Y });
		NewDoor->DoorRenderer->SetComponentLocation({ _Pos.X + 370.0f, _Pos.Y });

		break;
	case RoomDir::DOWN:
		NewDoor->DoorRenderer->CreateAnimation("DownNormalRoomDoor_Idle", "NormalRoomDoor.png", 3, 3, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("DownNormalRoomDoor_Idle");
		NewDoor->SetActorLocation({ _Pos.X, _Pos.Y + 215.0f });
		NewDoor->DoorRenderer->SetComponentLocation({ _Pos.X, _Pos.Y + 215.0f });

		break;
	case RoomDir::LEFT:
		NewDoor->DoorRenderer->CreateAnimation("LeftNormalRoomDoor_Idle", "NormalRoomDoor.png", 0, 0, 0.1f);
		NewDoor->DoorRenderer->ChangeAnimation("LeftNormalRoomDoor_Idle");
		NewDoor->SetActorLocation({ _Pos.X - 370.0f, _Pos.Y });
		NewDoor->DoorRenderer->SetComponentLocation({ _Pos.X - 370.0f, _Pos.Y });

		break;
	default:
		break;
	}

	//U2DCollision* CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	//CollisionComponent->SetComponentLocation(NewDoor->GetActorLocation());
	//CollisionComponent->SetComponentScale({ 50, 70 });
	//CollisionComponent->SetCollisionGroup(ECollisionGroup::Door);
	//CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();

	NewDoor->LinkedRoom = _LinkRoom;
	Doors.insert({ _Dir,NewDoor });
}

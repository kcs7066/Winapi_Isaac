#include "PreCompile.h"
#include "TrapDoor.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include <EngineCore/EngineAPICore.h>


ATrapDoor::ATrapDoor()
{
	SetActorLocation({ 200, 0 });

	{
		TrapDoorRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TrapDoorRenderer->SetComponentScale({ 100, 100 });
		TrapDoorRenderer->CreateAnimation("Idle_TrapDoor", "TrapDoor.png", 1, 1, 0.1f);
		TrapDoorRenderer->ChangeAnimation("Idle_TrapDoor");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::TrapDoor);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

void ATrapDoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


		AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);


		if (nullptr != Result)
		{
			AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);

			UEngineAPICore::GetCore()->OpenLevel("Title");
			Destroy();
		}
	

}

ATrapDoor::~ATrapDoor()
{
}

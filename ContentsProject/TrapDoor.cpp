#include "PreCompile.h"
#include "TrapDoor.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include <EngineCore/EngineAPICore.h>
#include "PlayGameMode.h"



ATrapDoor::ATrapDoor()
{

	{
		TrapDoorRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TrapDoorRenderer->SetComponentScale({ 130, 130 });
		TrapDoorRenderer->CreateAnimation("Idle_TrapDoor", "TrapDoor.png", 1, 1, 0.1f);
		TrapDoorRenderer->ChangeAnimation("Idle_TrapDoor");
	}



	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50,50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::TrapDoor);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	DebugOn();
}

ATrapDoor::~ATrapDoor()
{
}

void ATrapDoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);


	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);
		APlayGameMode* Mode = GetWorld()->GetGameMode<APlayGameMode>();
		Mode->BGMPlayer.Off();
		UEngineAPICore::GetCore()->OpenLevel("Title");
		Destroy();
	}


}


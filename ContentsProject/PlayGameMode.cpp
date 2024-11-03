#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Room.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}


void APlayGameMode::BeginPlay()
{
	
 APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();

 ARoom* FirstRoom = GetWorld()->SpawnActor<ARoom>();
	
}
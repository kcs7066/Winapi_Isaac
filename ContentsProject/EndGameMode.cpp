#include "PreCompile.h"
#include "EndGameMode.h"

#include <EngineCore/Level.h>
#include "EndingCredit.h"

AEndGameMode::AEndGameMode()
{
}

AEndGameMode::~AEndGameMode()
{
}

void AEndGameMode::BeginPlay()
{
	{
		AEndingCredit* NewActor = GetWorld()->SpawnActor<AEndingCredit>();
	}
}
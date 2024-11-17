#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>



ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();
	BGMPlayer = UEngineSound::Play("title screen.ogg");
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		BGMPlayer.Off();
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}

}
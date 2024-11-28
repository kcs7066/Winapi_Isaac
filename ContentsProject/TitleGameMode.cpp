#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "TitleLogo.h"
#include "PlayGameMode.h"
#include "Isaac.h"



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
	BGMPlayer.Loop(100);

	UEngineAPICore::GetCore()->DestroyLevel("Play");
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		BGMPlayer.Off();
		UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, AIsaac>("Play");
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}

}
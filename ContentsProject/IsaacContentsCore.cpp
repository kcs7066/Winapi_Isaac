#include "PreCompile.h"
#include "IsaacContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

IsaacContentsCore::IsaacContentsCore()
{
}

IsaacContentsCore::~IsaacContentsCore()
{
}

void IsaacContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Isaac");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void IsaacContentsCore::Tick()
{
}

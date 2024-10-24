#include "PreCompile.h"
#include "IsaacContentsCore.h"
#include <EngineCore/EngineAPICore.h>

IsaacContentsCore::IsaacContentsCore()
{
}

IsaacContentsCore::~IsaacContentsCore()
{
}

void IsaacContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");

}

void IsaacContentsCore::Tick()
{
}

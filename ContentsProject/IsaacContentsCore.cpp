#include "PreCompile.h"
#include "IsaacContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

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
	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("IsaacResource"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Isaac");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void IsaacContentsCore::Tick()
{
}

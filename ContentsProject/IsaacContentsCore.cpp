#include "PreCompile.h"
#include "IsaacContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
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

	UImageManager::GetInst().CuttingSprite("Test_Loki.png", { 128, 128 });
	UImageManager::GetInst().CuttingSprite("Test_Monstro.png", { 512, 512 });

	{

		UEngineDirectory TitleDir;
		TitleDir.MoveParentToDirectory("IsaacResource");
		TitleDir.Append("Title");

		UImageManager::GetInst().LoadFolder(TitleDir.GetPathToString());

	}

	{

		UEngineDirectory PlayDir;
		PlayDir.MoveParentToDirectory("IsaacResource");
		PlayDir.Append("Play");

		UImageManager::GetInst().LoadFolder(PlayDir.GetPathToString());

	}



	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Isaac");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 960, 540 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void IsaacContentsCore::Tick()
{
}

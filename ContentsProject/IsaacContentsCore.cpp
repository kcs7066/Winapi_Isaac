#include "PreCompile.h"
#include "IsaacContentsCore.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "Isaac.h"

IsaacContentsCore::IsaacContentsCore()
{
}

IsaacContentsCore::~IsaacContentsCore()
{
}

void IsaacContentsCore::BeginPlay()
{

	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("IsaacResource"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}

		Dir.Append("Image");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("IsaacResource"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	

	UImageManager::GetInst().CuttingSprite("Head.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Body.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("NormalRoomDoor.png", { 256, 256 });
	UImageManager::GetInst().CuttingSprite("GoldRoomDoor.png", { 256, 256 });
	UImageManager::GetInst().CuttingSprite("BossRoomDoor.png", { 256, 256 });
	UImageManager::GetInst().CuttingSprite("Tear.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("TearPoof.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("BloodTearPoof.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Fly.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Roundworm.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Dip_Left.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Monster_Dip_Right.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Monster_Spider.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_BabyLongLegs.png", { 128, 128 });
	UImageManager::GetInst().CuttingSprite("Monster_LevelTwoSpiderSmall.png", { 48, 32 });
	UImageManager::GetInst().CuttingSprite("Boss_Monstro.png", { 128, 128 });
	UImageManager::GetInst().CuttingSprite("Structure_Rock.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Structure_Poop_1.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("TrapDoor.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("BloodPoof.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Pickup_Bomb.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Effect_Explosion.png", { 128, 128 });
	UImageManager::GetInst().CuttingSprite("Boss_Larryjr_Left.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Boss_Larryjr_Right.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Ui_Hearts.png", { 16, 16 });
	UImageManager::GetInst().CuttingSprite("Number.png", { 16, 16 });
	UImageManager::GetInst().CuttingSprite("HUDPickups.png", { 16, 16 });
	UImageManager::GetInst().CuttingSprite("Pickup_Coin.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Pickup_Key.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Pickup_Heart.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Character_Isaac.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Ghost.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Minimap2.png", { 16, 16 });
	UImageManager::GetInst().CuttingSprite("Minimap_Icons.png", { 16, 16 });
	UImageManager::GetInst().CuttingSprite("Character_IsaacItem.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Monster_Gaper.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Monster_Pacer.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Pacer_Left.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Fatty.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Fatty_Left.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Effect_Poof.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Monster_Pooter.png", { 32, 32 });
	UImageManager::GetInst().CuttingSprite("Costume.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Ui_BossHealthBar.png", { 150, 32 });

	{

		UEngineDirectory TitleDir;
		TitleDir.MoveParentToDirectory("IsaacResource");
		TitleDir.Append("Title");

		UImageManager::GetInst().LoadFolder(TitleDir.GetPathToString());

	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("The Binding Of Isaac");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 960, 540 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void IsaacContentsCore::Tick()
{
}

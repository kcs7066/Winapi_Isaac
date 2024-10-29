#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>

#include <EnginePlatform/EngineWinImage.h>

class UImageManager
{
public:
	// constrcuter destructer
	~UImageManager();

	// delete Function
	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

	static UImageManager& GetInst()
	{
		static UImageManager Inst;
		return Inst;
	}

	void Load(std::string_view Path);

protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*> Images;
};

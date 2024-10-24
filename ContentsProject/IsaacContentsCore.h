#pragma once
#include <EngineCore/EngineAPICore.h>

class IsaacContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	IsaacContentsCore();
	~IsaacContentsCore();

	// delete Function
	IsaacContentsCore(const IsaacContentsCore& _Other) = delete;
	IsaacContentsCore(IsaacContentsCore&& _Other) noexcept = delete;
	IsaacContentsCore& operator=(const IsaacContentsCore& _Other) = delete;
	IsaacContentsCore& operator=(IsaacContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:

};


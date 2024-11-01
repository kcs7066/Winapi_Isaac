#pragma once
#include <EngineCore/Actor.h>

class AEndingCredit : public AActor
{
public:
	// constrcuter destructer
	AEndingCredit();
	~AEndingCredit();

	// delete Function
	AEndingCredit(const AEndingCredit& _Other) = delete;
	AEndingCredit(AEndingCredit&& _Other) noexcept = delete;
	AEndingCredit& operator=(const AEndingCredit& _Other) = delete;
	AEndingCredit& operator=(AEndingCredit&& _Other) noexcept = delete;

protected:

private:

};


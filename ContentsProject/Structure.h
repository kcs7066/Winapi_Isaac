#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AStructure : public AActor
{
public:
	// constrcuter destructer
	AStructure();
	~AStructure();

	// delete Function
	AStructure(const AStructure& _Other) = delete;
	AStructure(AStructure&& _Other) noexcept = delete;
	AStructure& operator=(const AStructure& _Other) = delete;
	AStructure& operator=(AStructure&& _Other) noexcept = delete;

protected:



private:

};


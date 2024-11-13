#pragma once
#include "Structure.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

class APoop : public AStructure
{
public:
	// constrcuter destructer
	APoop();
	~APoop();

	// delete Function
	APoop(const APoop& _Other) = delete;
	APoop(APoop&& _Other) noexcept = delete;
	APoop& operator=(const APoop& _Other) = delete;
	APoop& operator=(APoop&& _Other) noexcept = delete;

protected:

private:

	USpriteRenderer* PoopRenderer;
	U2DCollision* CollisionComponent;
};


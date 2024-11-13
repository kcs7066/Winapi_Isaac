#pragma once
#include "Structure.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

class ARock : public AStructure
{
public:
	// constrcuter destructer
	ARock();
	~ARock();

	// delete Function
	ARock(const ARock& _Other) = delete;
	ARock(ARock&& _Other) noexcept = delete;
	ARock& operator=(const ARock& _Other) = delete;
	ARock& operator=(ARock&& _Other) noexcept = delete;

protected:

private:

	USpriteRenderer* RockRenderer;
	U2DCollision* CollisionComponent;
};


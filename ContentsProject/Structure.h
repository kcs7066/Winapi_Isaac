#pragma once
#include <EngineCore/Actor.h>

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

	FVector2D Pos;

	int Hp = 4;

	class USpriteRenderer* StructureRenderer;
	class U2DCollision* CollisionComponent;

protected:

private:

};


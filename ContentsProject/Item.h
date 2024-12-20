#pragma once
#include <EngineCore/Actor.h>


class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	class USpriteRenderer* ItemRenderer = nullptr;
	class U2DCollision* CollisionComponent;

protected:

private:

	class USpriteRenderer* ShadowRenderer = nullptr;
	class USpriteRenderer* AlterRenderer = nullptr;

};


#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

class APickUp : public AActor
{
public:
	// constrcuter destructer
	APickUp();
	~APickUp();

	// delete Function
	APickUp(const APickUp& _Other) = delete;
	APickUp(APickUp&& _Other) noexcept = delete;
	APickUp& operator=(const APickUp& _Other) = delete;
	APickUp& operator=(APickUp&& _Other) noexcept = delete;


	class USpriteRenderer* ShadowRenderer = nullptr;
	class USpriteRenderer* PickUpRenderer;
	U2DCollision* CollisionComponent;

protected:



private:


};


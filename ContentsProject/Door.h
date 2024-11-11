#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>


class ADoor : public AActor
{
public:
	// constrcuter destructer
	ADoor();
	~ADoor();

	// delete Function
	ADoor(const ADoor& _Other) = delete;
	ADoor(ADoor&& _Other) noexcept = delete;
	ADoor& operator=(const ADoor& _Other) = delete;
	ADoor& operator=(ADoor&& _Other) noexcept = delete;

	class ARoom* LinkedRoom = nullptr;

	USpriteRenderer* DoorRenderer;

protected:

private:
	U2DCollision* CollisionComponent;
};


#pragma once
#include <EngineCore/Actor.h>

class ATrapDoor : public AActor
{
public:
	// constrcuter destructer
	ATrapDoor();
	~ATrapDoor();

	// delete Function
	ATrapDoor(const ATrapDoor& _Other) = delete;
	ATrapDoor(ATrapDoor&& _Other) noexcept = delete;
	ATrapDoor& operator=(const ATrapDoor& _Other) = delete;
	ATrapDoor& operator=(ATrapDoor&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

protected:

private:

	class USpriteRenderer* TrapDoorRenderer;
	class U2DCollision* CollisionComponent;
};


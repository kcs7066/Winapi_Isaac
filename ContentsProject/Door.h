#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>

enum class DoorDir
{
	NONE = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4

};

enum class DoorType
{
	NORMAL,
	GOLD,
	BOSS
};

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

	void DoorOpen();


	class ARoom* LinkedRoom = nullptr;

	USpriteRenderer* DoorRenderer = nullptr;
	DoorDir Dir = DoorDir::NONE;
	DoorType Type = DoorType::NORMAL;

protected:

private:
	U2DCollision* CollisionComponent;
};


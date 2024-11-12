#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/2DCollision.h>

class AMonsterTear : public AActor
{
public:
	// constrcuter destructer
	AMonsterTear();
	~AMonsterTear();

	// delete Function
	AMonsterTear(const AMonsterTear& _Other) = delete;
	AMonsterTear(AMonsterTear&& _Other) noexcept = delete;
	AMonsterTear& operator=(const AMonsterTear& _Other) = delete;
	AMonsterTear& operator=(AMonsterTear&& _Other) noexcept = delete;
	FVector2D Dir = FVector2D::ZERO;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	class USpriteRenderer* SpriteRenderer;
	U2DCollision* CollisionComponent;

	float BulletSpeed = 1.0f;
};
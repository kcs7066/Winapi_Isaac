#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>


enum class FlyState
{
	Move,
	Die
};

class AFly : public AMonster
{
public:
	// constrcuter destructer
	AFly();
	~AFly();

	// delete Function
	AFly(const AFly& _Other) = delete;
	AFly(AFly&& _Other) noexcept = delete;
	AFly& operator=(const AFly& _Other) = delete;
	AFly& operator=(AFly&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);

protected:

private:
	float Speed = 500.0f;
	FVector2D RandomDir;

};
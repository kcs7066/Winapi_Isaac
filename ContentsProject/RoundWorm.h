#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>


enum class RoundWormState
{
	Idle,
	Attack,
	Idle2,
	Move,
	Die

};

class ARoundWorm : public AMonster
{
public:
	// constrcuter destructer
	ARoundWorm();
	~ARoundWorm();

	// delete Function
	ARoundWorm(const ARoundWorm& _Other) = delete;
	ARoundWorm(ARoundWorm&& _Other) noexcept = delete;
	ARoundWorm& operator=(const ARoundWorm& _Other) = delete;
	ARoundWorm& operator=(ARoundWorm&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Idle2(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);

protected:

private:
	float BulletCoolTime = 0.5f;

	float Speed = 500.0f;


};


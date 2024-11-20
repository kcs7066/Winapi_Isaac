#pragma once
#include "Monster.h"


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
	void DieStart();

	bool FindPos = false;

protected:

private:
	float TearCoolTime = 0.5f;

	float Speed = 500.0f;

	
};


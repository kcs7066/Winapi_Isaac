#pragma once
#include "Monster.h"

enum class MonstroState
{
	Idle,
	Move,
	Attack,
	Jump,
	Die


};

class AMonstro : public AMonster
{
public:
	// constrcuter destructer
	AMonstro();
	~AMonstro();

	// delete Function
	AMonstro(const AMonstro& _Other) = delete;
	AMonstro(AMonstro&& _Other) noexcept = delete;
	AMonstro& operator=(const AMonstro& _Other) = delete;
	AMonstro& operator=(AMonstro&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();

protected:

private:

	float TearCoolTime = 1.5f;
	float Speed = 300.0f;
	bool JumpValue = true;
	bool JumpValue2 = true;

	FVector2D Dir;
};


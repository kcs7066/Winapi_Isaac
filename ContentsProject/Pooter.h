#pragma once
#include "Monster.h"

enum class PooterState
{
	Move,
	Attack,
	Die

};

class APooter : public AMonster
{
public:
	// constrcuter destructer
	APooter();
	~APooter();

	// delete Function
	APooter(const APooter& _Other) = delete;
	APooter(APooter&& _Other) noexcept = delete;
	APooter& operator=(const APooter& _Other) = delete;
	APooter& operator=(APooter&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);
	void AttackStart();
	void Die(float _DeltaTime);
	void DieStart();


protected:

private:
	float Speed = 500.0f;
	float TearSpeed = 0.7f;
	float TearCoolTime = 0.0f;

	FVector2D RandomDir;

	class U2DCollision* AttackRadius = nullptr;
};
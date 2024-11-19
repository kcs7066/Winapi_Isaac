#pragma once
#include "Monster.h"


enum class  RedFlyState
{
	Idle,
	Move,
	Die


};

class ARedFly : public AMonster
{
public:
	// constrcuter destructer
	ARedFly();
	~ARedFly();

	// delete Function
	ARedFly(const ARedFly& _Other) = delete;
	ARedFly(ARedFly&& _Other) noexcept = delete;
	ARedFly& operator=(const ARedFly& _Other) = delete;
	ARedFly& operator=(ARedFly&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();
	
protected:

private:

	FVector2D Dir;
	float Speed = 100.0f;

	
};
#pragma once
#include "Monster.h"


enum class PurpleFlyState
{
	Move,
	Die

};

class APurpleFly : public AMonster
{
public:
	// constrcuter destructer
	APurpleFly();
	~APurpleFly();

	// delete Function
	APurpleFly(const APurpleFly& _Other) = delete;
	APurpleFly(APurpleFly&& _Other) noexcept = delete;
	APurpleFly& operator=(const APurpleFly& _Other) = delete;
	APurpleFly& operator=(APurpleFly&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void DieStart();


protected:

private:

	float Speed = 500.0f;
	FVector2D Dir = { 1,0 };

};


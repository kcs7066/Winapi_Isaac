#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class PurpleFlyState
{
	Move,
	Die,
	DieStay
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
	void DieStay(float _DeltaTime);


protected:

private:

	float Speed = 500.0f;
	FVector2D Dir = { 1,0 };

};


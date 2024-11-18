#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>



enum class  RedFlyState
{
	Idle,
	Move,
	Die,
	DieStay

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
	void DieStay(float _DeltaTime);
	
protected:

private:

	FVector2D Dir;
	float Speed = 100.0f;

	
};
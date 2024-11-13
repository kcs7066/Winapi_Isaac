#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class  RedFlyState
{
	Idle,
	Move

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

protected:

private:

	FVector2D Dir;

	U2DCollision* CollisionComponent;
	float Speed = 100.0f;
	class USpriteRenderer* RedFlyRenderer = nullptr;
	

	UFSMStateManager FSM = UFSMStateManager();
	

};
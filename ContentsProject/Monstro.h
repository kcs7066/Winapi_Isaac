#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class MonstroState
{
	Idle,
	Move,
	Attack,
	Jump

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


protected:

private:
	float BulletCoolTime = 1.5f;

	float DelayTime = 0.0f;

	U2DCollision* CollisionComponent;
	float Speed = 300.0f;
	class USpriteRenderer* MonstroRenderer = nullptr;

	FVector2D Dir;

	UFSMStateManager FSM = UFSMStateManager();
	UEngineRandom Random;

};


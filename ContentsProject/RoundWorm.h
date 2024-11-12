#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class RoundWormState
{
	Idle,
	Attack,
	Idle2,
	Move

};

class ARoundWorm : public AActor
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
	

protected:

private:
	float BulletCoolTime = 0.5f;

	float DelayTime = 0.0f;

	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class USpriteRenderer* RoundWormRenderer = nullptr;

	UFSMStateManager FSM = UFSMStateManager();
	UEngineRandom Random;

};


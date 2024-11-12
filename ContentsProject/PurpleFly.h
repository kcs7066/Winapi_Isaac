#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class NewMonsterState
{
	Idle,
	Move

};

class APurpleFly : public AActor
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

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

protected:

private:
	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class USpriteRenderer* PurpleFlyRenderer = nullptr;

	UFSMStateManager FSM = UFSMStateManager();

};


#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class FlyState
{
	Idle,
	Move

};

class AFly : public AMonster
{
public:
	// constrcuter destructer
	AFly();
	~AFly();

	// delete Function
	AFly(const AFly& _Other) = delete;
	AFly(AFly&& _Other) noexcept = delete;
	AFly& operator=(const AFly& _Other) = delete;
	AFly& operator=(AFly&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);


protected:

private:


	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class USpriteRenderer* FlyRenderer = nullptr;
	FVector2D RandomDir;

	UFSMStateManager FSM = UFSMStateManager();
	UEngineRandom Random;

};
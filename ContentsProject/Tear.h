#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/FSMStateManager.h>

enum class TearState
{
	Fly,
	Poof
};

class ATear : public AActor
{
public:
	// constrcuter destructer
	ATear();
	~ATear();

	// delete Function
	ATear(const ATear& _Other) = delete;
	ATear(ATear&& _Other) noexcept = delete;
	ATear& operator=(const ATear& _Other) = delete;
	ATear& operator=(ATear&& _Other) noexcept = delete;
	FVector2D Dir = FVector2D::ZERO;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Fly(float _DeltaTime);
	void Poof(float _DeltaTime);

	float DelayTime = 0.0f;
	float DropPos = 0.0f;

private:
	class USpriteRenderer* TearRenderer;
	class USpriteRenderer* ShadowRenderer;
	U2DCollision* CollisionComponent;

	float Speed = 500.0f;
	UFSMStateManager FSM = UFSMStateManager();
};
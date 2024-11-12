#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class DipState
{
	IdleRight,
	IdleLeft,
	MoveRight,
	MoveLeft
};

class ASpider : public AActor
{
public:
	// constrcuter destructer
	ASpider();
	~ASpider();

	// delete Function
	ASpider(const ASpider& _Other) = delete;
	ASpider(ASpider&& _Other) noexcept = delete;
	ASpider& operator=(const ASpider& _Other) = delete;
	ASpider& operator=(ASpider&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);


protected:
	void TimeEvent();

private:

	float DelayTime = 0.0f;

	UFSMStateManager FSM = UFSMStateManager();
	U2DCollision* CollisionComponent;
	float Speed = 300.0f;
	class USpriteRenderer* SpiderRenderer = nullptr;
	FVector2D RandomDir = { 0,0 };

	UEngineRandom Random;

};
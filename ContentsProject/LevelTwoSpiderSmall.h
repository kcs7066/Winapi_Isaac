#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>

enum class LevelTwoSpiderSmallState
{
	Idle,
	Move,
	Jump

};

class ALevelTwoSpiderSmall : public AMonster
{
public:
	// constrcuter destructer
	ALevelTwoSpiderSmall();
	~ALevelTwoSpiderSmall();

	// delete Function
	ALevelTwoSpiderSmall(const ALevelTwoSpiderSmall& _Other) = delete;
	ALevelTwoSpiderSmall(ALevelTwoSpiderSmall&& _Other) noexcept = delete;
	ALevelTwoSpiderSmall& operator=(const ALevelTwoSpiderSmall& _Other) = delete;
	ALevelTwoSpiderSmall& operator=(ALevelTwoSpiderSmall&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);


protected:

private:

	float DelayTime = 0.0f;

	UFSMStateManager FSM = UFSMStateManager();
	U2DCollision* CollisionComponent;
	float Speed = 300.0f;
	class USpriteRenderer* LevelTwoSpiderSmallRenderer = nullptr;
	FVector2D Dir = { 0,0 };
	UEngineRandom Random;


};
#pragma once

#include <EngineBase/EngineRandom.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/Actor.h>



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

private:

	float DelayTime = 0.0f;
	float DropPos = 0.0f;
	float TearSpeed = 450.0f;

	class USpriteRenderer* TearRenderer;
	class USpriteRenderer* ShadowRenderer;
	class U2DCollision* CollisionComponent;

	UFSMStateManager FSM = UFSMStateManager();
	USoundPlayer EffectPlayer;
	USoundPlayer PoopPlayer;
	UEngineRandom Random;

};
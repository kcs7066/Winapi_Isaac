#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/FSMStateManager.h>
#include <EnginePlatform/EngineSound.h>

enum class BombState
{
	Idle,
	Explosion,
	ExplosionStay
};

class ABomb : public AActor
{
public:
	// constrcuter destructer
	ABomb();
	~ABomb();

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void Explosion(float _DeltaTime);
	void ExplosionStay(float _DeltaTime);
	float DelayTime = 0.0f;


private:

	UFSMStateManager FSM = UFSMStateManager();
	class USpriteRenderer* BombRenderer;
	class USpriteRenderer* ShadowRenderer;
	U2DCollision* CollisionComponent;

};


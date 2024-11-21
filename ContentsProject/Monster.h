#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void SetHp(float _Value)
	{
		Hp = _Value;
	}


	bool DeathValue = false;
	float DelayTime = 0.0f;
	float Hp = 1.0f;

	class USpriteRenderer* ShadowRenderer = nullptr;
	class USpriteRenderer* MonsterRenderer = nullptr;
	class USpriteRenderer* PoofRenderer = nullptr;
	class U2DCollision* CollisionComponent = nullptr;

	UFSMStateManager FSM;
	UEngineRandom Random;
	USoundPlayer EffectPlayer;



protected:



private:

	
};


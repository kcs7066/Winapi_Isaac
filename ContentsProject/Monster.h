#pragma once
#include <EngineCore/Actor.h>

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

	bool DeathCheck()
	{
		return Hp <= 0.0f;
	}

	float Hp = 1.0f;

	//void SetSeed()
	//{
	//	Random
	//}

	//UEngineRandom Random;

protected:



private:

};


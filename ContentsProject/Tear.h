#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>

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


	void Tick(float _DeltaTime) override;

private:
	class USpriteRenderer* SpriteRenderer;

	float BulletSpeed = 500.0f;
};
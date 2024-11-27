#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AFade : public AActor
{
public:
	static AFade* MainFade;

public:
	// constrcuter destructer
	AFade();
	~AFade();

	// delete Function
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	void FadeIn();
	void FadeOut();

	float FadeValue = 0.0f;

	USpriteRenderer* BackSpriteRenderer;
protected:

private:

	float FadeDir = 1.0f;

	void LevelChangeStart() override;
	void FadeChange();

};


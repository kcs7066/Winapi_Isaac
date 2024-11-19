#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class AUi : public AActor
{
public:
	// constrcuter destructer
	AUi();
	~AUi();

	// delete Function
	AUi(const AUi& _Other) = delete;
	AUi(AUi&& _Other) noexcept = delete;
	AUi& operator=(const AUi& _Other) = delete;
	AUi& operator=(AUi&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetValue(int _Score);
	class USpriteRenderer* HUDRenderer;
	int Number = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;
	


};


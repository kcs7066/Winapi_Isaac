#pragma once
#include "PickUp.h"

class APickUpHeart : public APickUp
{
public:
	// constrcuter destructer
	APickUpHeart();
	~APickUpHeart();

	// delete Function
	APickUpHeart(const APickUpHeart& _Other) = delete;
	APickUpHeart(APickUpHeart&& _Other) noexcept = delete;
	APickUpHeart& operator=(const APickUpHeart& _Other) = delete;
	APickUpHeart& operator=(APickUpHeart&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};


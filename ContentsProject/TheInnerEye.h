#pragma once
#include "Item.h"

class ATheInnerEye : public AItem
{
public:
	// constrcuter destructer
	ATheInnerEye();
	~ATheInnerEye();

	// delete Function
	ATheInnerEye(const ATheInnerEye& _Other) = delete;
	ATheInnerEye(ATheInnerEye&& _Other) noexcept = delete;
	ATheInnerEye& operator=(const ATheInnerEye& _Other) = delete;
	ATheInnerEye& operator=(ATheInnerEye&& _Other) noexcept = delete;

protected:

private:

};


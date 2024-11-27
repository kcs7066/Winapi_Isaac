#include "PreCompile.h"
#include "TheInnerEye.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

ATheInnerEye::ATheInnerEye()
	:AItem()
{
	ItemRenderer->SetSprite("Item_TheInnerEye.png");
	ItemRenderer->SetSpriteScale(2.0f);

	DebugOn();
}

ATheInnerEye::~ATheInnerEye()
{
}


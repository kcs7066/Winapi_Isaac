#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	
	SpriteRenderer->CreateAnimation("TitleAnimation", "Title", 0, 1, 0.1f,true);
	SpriteRenderer->ChangeAnimation("TitleAnimation");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
}

TitleLogo::~TitleLogo()
{
}



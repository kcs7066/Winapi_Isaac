#include "PreCompile.h"
#include "Tear.h"
#include <EngineCore/SpriteRenderer.h>
#include "Isaac.h"

ATear::ATear()
{	

    {
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Tear.png");
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->CreateAnimation("Tear_Fly", "Tear.png", 0, 4, 0.1f);
		SpriteRenderer->ChangeAnimation("Tear_Fly");
	}

}

ATear::~ATear()
{
}

void ATear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AddActorLocation(Dir * _DeltaTime * 300.0f);
	
}
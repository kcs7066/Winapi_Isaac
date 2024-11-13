#include "PreCompile.h"
#include "Tear.h"
#include <EngineCore/SpriteRenderer.h>
#include "Isaac.h"
#include "ContentsEnum.h"
#include "PlayGameMode.h"
#include "Monster.h"

ATear::ATear()
{	
	
    {
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Tear.png");
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->CreateAnimation("Tear_Fly", "Tear.png", 0, 4, 0.1f);
		SpriteRenderer->ChangeAnimation("Tear_Fly");
	}

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 30, 30 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::Tear);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	}

}

ATear::~ATear()
{
}

void ATear::BeginPlay()
{
	AActor::BeginPlay();
}
void ATear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AddActorLocation(Dir * _DeltaTime * 300.0f);
	
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Monster);

	if (nullptr != Result)
	{
		AMonster* NewResult = dynamic_cast<AMonster*>(Result);

		NewResult->Hp -= 100.0f;

		Destroy();
	}
}
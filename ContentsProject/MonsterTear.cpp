#include "PreCompile.h"
#include "MonsterTear.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AMonsterTear::AMonsterTear()
{

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->CreateAnimation("MonsterTear_Fly", "Tear.png", 13, 17, 0.1f);
		SpriteRenderer->ChangeAnimation("MonsterTear_Fly");
	}

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 30, 30 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::MonsterTear);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	}

}

AMonsterTear::~AMonsterTear()
{
}

void AMonsterTear::BeginPlay()
{
	AActor::BeginPlay();
}
void AMonsterTear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AddActorLocation(Dir * _DeltaTime * BulletSpeed);
	Destroy(2.0f);
}
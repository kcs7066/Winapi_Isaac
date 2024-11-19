#include "PreCompile.h"
#include "Monster.h"

AMonster::AMonster()
	: AActor()
{

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 50, 50 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

}

AMonster::~AMonster()
{
}


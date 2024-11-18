#include "PreCompile.h"
#include "PickUpBomb.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include "PlayGameMode.h"

APickUpBomb::APickUpBomb()
{

	SetActorLocation({ 200,0 });

	
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.3f);
	


	PickUpRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PickUpRenderer->SetOrder(ERenderOrder::PICKUP);
	PickUpRenderer->SetComponentScale({ 70, 70 });
	PickUpRenderer->SetComponentLocation({ -2, -16 });
	PickUpRenderer->CreateAnimation("Idle_Bomb", "Pickup_Bomb.png", 0, 0, 0.1f);
	PickUpRenderer->ChangeAnimation("Idle_Bomb");

	
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 35, 35 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PickUp);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	
}

APickUpBomb::~APickUpBomb()
{
}

void APickUpBomb::BeginPlay()
{

}

void APickUpBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);

		NewResult->BombNumber++;
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->BombUi->SetValue(NewResult->BombNumber);
		Destroy();
	}
	
}
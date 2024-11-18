#include "PreCompile.h"
#include "PickUpHeart.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include "PlayGameMode.h"

APickUpHeart::APickUpHeart()
{

	SetActorLocation({ 200,0 });

	
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.3f);
	


	PickUpRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PickUpRenderer->SetOrder(ERenderOrder::PICKUP);
	PickUpRenderer->SetComponentScale({ 70,70 });
	PickUpRenderer->SetComponentLocation({ 0,-10 });
	PickUpRenderer->CreateAnimation("Idle_Heart", "Pickup_Heart.png", 0, 0, 0.1f);
	PickUpRenderer->ChangeAnimation("Idle_Heart");

	
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 35, 35 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PickUp);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	
}

APickUpHeart::~APickUpHeart()
{
}

void APickUpHeart::BeginPlay()
{

}

void APickUpHeart::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);

		NewResult->Hp += 2;
		//APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		//PlayGameMode->HeartUi->SetValue(NewResult->HeartNumber);
		Destroy();
	}

}
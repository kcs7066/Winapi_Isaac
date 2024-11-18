#include "PreCompile.h"
#include "PickUpCoin.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include "PlayGameMode.h"

APickUpCoin::APickUpCoin()
{

	SetActorLocation({ 200,0 });

	
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.3f);
	


	PickUpRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PickUpRenderer->SetOrder(ERenderOrder::PICKUP);
	PickUpRenderer->SetComponentScale({ 130, 130 });
	PickUpRenderer->SetComponentLocation({ 0,0 });
	PickUpRenderer->CreateAnimation("Idle_Coin", "Pickup_Coin.png", 0 , 5 , 0.1f);
	PickUpRenderer->ChangeAnimation("Idle_Coin");

	
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 35, 35 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PickUp);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	
}

APickUpCoin::~APickUpCoin()
{
}

void APickUpCoin::BeginPlay()
{

}

void APickUpCoin::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);

		NewResult->CoinNumber++;
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CoinUi->SetValue(NewResult->CoinNumber);
		Destroy();
	}

}


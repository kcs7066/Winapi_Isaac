#include "PreCompile.h"
#include "PickUpKey.h"
#include "ContentsEnum.h"
#include "Isaac.h"
#include "PlayGameMode.h"

APickUpKey::APickUpKey()
{

	SetActorLocation({ 200,0 });

	
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.1f);
	


	PickUpRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PickUpRenderer->SetOrder(ERenderOrder::PICKUP);
	PickUpRenderer->SetComponentScale({ 60, 60 });
	PickUpRenderer->SetComponentLocation({ 0,-20 });
	PickUpRenderer->CreateAnimation("Idle_Key", "Pickup_Key.png", 0, 0, 0.1f);
	PickUpRenderer->ChangeAnimation("Idle_Key");

	
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale({ 45, 45 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PickUp);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		DebugOn();
	
}

APickUpKey::~APickUpKey()
{
}

void APickUpKey::BeginPlay()
{

}

void APickUpKey::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Player);
	if (nullptr != Result)
	{
		AIsaac* NewResult = dynamic_cast<AIsaac*>(Result);

		NewResult->KeyNumber++;
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->KeyUi->SetValue(NewResult->KeyNumber);
		Destroy();
	}

}
#include "PreCompile.h"
#include "Larryjr.h"

#include <EnginePlatform/EngineInput.h>
#include "PlayGameMode.h"
#include "TrapDoor.h"
#include "Poop.h"


ALarryjr::ALarryjr()
{
	SetActorLocation({ 200, 0 });

	{
		MonsterRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MonsterRenderer->SetOrder(ERenderOrder::MONSTER);

		MonsterRenderer->SetComponentScale({ 100, 100 });
		MonsterRenderer->SetComponentLocation({ 0,-40 });

		MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Left", "Boss_Larryjr_Left.png", 0, 1, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Up", "Boss_Larryjr_Left.png", 2, 3, 0.1f);
		MonsterRenderer->CreateAnimation("Head_Larryjr_Down", "Boss_Larryjr_Left.png", 4, 5, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Left", "Boss_Larryjr_Left.png", 6, 7, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Down", "Boss_Larryjr_Left.png", 8, 9, 0.1f);
		MonsterRenderer->CreateAnimation("Tail_Larryjr_Up", "Boss_Larryjr_Left.png", 10, 11, 0.1f);
		MonsterRenderer->CreateAnimation("Body_Larryjr_Up", "Boss_Larryjr_Left.png", 12, 13, 0.1f);


		MonsterRenderer->ChangeAnimation("Head_Larryjr_Right");
	}

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetSpriteScale(0.5f);


	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 100, 100 });
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Monster);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	DebugOn();

	SetHp(250.0f);

}

ALarryjr::~ALarryjr()
{
}

void ALarryjr::BeginPlay()
{
	Super::BeginPlay();



	FSM.CreateState(LarryjrState::Move, std::bind(&ALarryjr::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		}
	);

	FSM.CreateState(LarryjrState::Poop, std::bind(&ALarryjr::Poop, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		}
	);

	FSM.CreateState(LarryjrState::Separate, std::bind(&ALarryjr::Separate, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		}
	);

	FSM.CreateState(LarryjrState::Die, std::bind(&ALarryjr::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->CreateAnimation("Head_Larryjr_Right", "Boss_Larryjr_Right.png", 0, 1, 0.1f);
		}
	);


	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->BGMPlayer.Off();
	PlayGameMode->BGMPlayer = UEngineSound::Play("basic boss fight.ogg");
	FSM.ChangeState(LarryjrState::Move);
}

void ALarryjr::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);

}



void ALarryjr::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(MonstroState::Die);
	}

	if (DelayTime > 2.0f)
	{
		int RandomValue = Random.RandomInt(1, 3);

		switch (RandomValue)
		{
		case 1:
			FSM.ChangeState(MonstroState::Move);
			break;
		case 2:
			FSM.ChangeState(MonstroState::Attack);
			break;
		case 3:
			FSM.ChangeState(MonstroState::Jump);
			break;

		default:
			break;
		}

		DelayTime = 0.0f;
	}
}

void ALarryjr::Poop(float _DeltaTime)
{
	

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		ATrapDoor* NewTrapDoor = GetWorld()->SpawnActor<ATrapDoor>();
		NewTrapDoor->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 52.0f * (0.0f), PlayGameMode->CurRoom->RoomPos.Y - 52.0f * (2.0f) });
		DelayTime = 0.0f;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(LarryjrState::Die);
	}

	if (LarryjrPart::TAIL == this->Part)
	{
		APoop* NewPoop = GetWorld()->SpawnActor<APoop>();
		NewPoop->SetActorLocation(GetActorLocation());
	}

		FSM.ChangeState(LarryjrState::Move);

}

void ALarryjr::Separate(float _DeltaTime)
{
	

	if (this->Hp <= 0.0f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->CurRoom->MonsterNumber--;
		
		DelayTime = 0.0f;

		LinkedParts[Dir::Front]->Part = LarryjrPart::TAIL;
		LinkedParts[Dir::Back]->Part = LarryjrPart::HEAD;
		EffectPlayer = UEngineSound::Play("death burst large.wav");
		FSM.ChangeState(LarryjrState::Die);

	}

       FSM.ChangeState(LarryjrState::Move);

}

void ALarryjr::Die(float _DeltaTime)
{
	DeathValue = true;
	DelayTime += _DeltaTime;



	if (DelayTime > 1.1f)
	{
		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
		PlayGameMode->BGMPlayer.Off();
		PlayGameMode->BGMPlayer = UEngineSound::Play("secret to everyone.ogg");
		Destroy();
	}
}
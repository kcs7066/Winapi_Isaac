#include "PreCompile.h"
#include "Dip.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "PlayGameMode.h"
#include "Structure.h"
#include "ContentsEnum.h"



ADip::ADip()
	: AMonster()
{
	MonsterRenderer->SetComponentScale({ 70, 70 });
	MonsterRenderer->SetComponentLocation({ 0, -15 });

	MonsterRenderer->CreateAnimation("Idle_Dip_Left", "Monster_Dip_Left.png", 0, 1, 0.1f);
	MonsterRenderer->CreateAnimation("Idle_Dip_Right", "Monster_Dip_Right.png", 0, 1, 0.1f);
	MonsterRenderer->CreateAnimation("Move_Dip_Left", "Monster_Dip_Left.png", 0, 4, 0.1f);
	MonsterRenderer->CreateAnimation("Move_Dip_Right", "Monster_Dip_Right.png", 0, 4, 0.1f);
	MonsterRenderer->CreateAnimation("Die_Dip", "BloodPoof.png", 0, 10, 0.1f);

	MonsterRenderer->ChangeAnimation("Idle_Dip_Right");


	ShadowRenderer->SetSpriteScale(0.25f);

	CollisionComponent->SetComponentScale({ 30, 30 });

	DebugOn();

	SetHp(4.0f);
}

ADip::~ADip()
{
}

void ADip::BeginPlay()
{
	Super::BeginPlay();

	FSM.CreateState(DipState::IdleRight, std::bind(&ADip::Idle, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(DipState::IdleLeft, std::bind(&ADip::Idle, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(DipState::MoveLeft, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Dip_Left");
		}
	);

	FSM.CreateState(DipState::MoveRight, std::bind(&ADip::Move, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Move_Dip_Right");
		}
	);

	FSM.CreateState(DipState::Die, std::bind(&ADip::Die, this, std::placeholders::_1),
		[this]()
		{
			MonsterRenderer->ChangeAnimation("Die_Dip");
		}
	);

	FSM.ChangeState(DipState::IdleRight);
	float XValue = Random.Randomfloat(-0.5f, 0.5f);
	float YValue = Random.Randomfloat(-0.5f, 0.5f);
	if (0.0f > XValue)
	{
		XValue -= 0.25f;
	}
	else
	{
		XValue += 0.25f;
	}
	if (0.0f > YValue)
	{
		YValue -= 0.25f;
	}
	else
	{
		YValue += 0.25f;
	}

	RandomDir = { XValue ,YValue };

	RandomDir.Normalize();
}

void ADip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
    FSM.Update(_DeltaTime);
}

void ADip::Idle(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (DelayTime > 1.6f)
	{
		FSM.ChangeState(DipState::MoveRight);
		DelayTime = 0.0f;
	}
	if (this->Hp <= 0.0f)
	{
		DieStart();
	}
}

void ADip::Move(float _DeltaTime)
{
	DelayTime += _DeltaTime;
	PrevPos = GetActorLocation();
	FVector2D NewLocation = GetActorLocation() += RandomDir * _DeltaTime * Speed;
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X > 338.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.X - NewLocation.X < -338.0f)
	{
		RandomDir.X *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if (PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y > 182.0f)
	{
		RandomDir.Y *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else if(PlayGameMode->CurRoom->RoomPos.Y - NewLocation.Y < -182.0f)
	{
		RandomDir.Y *= (- 1.0f);
		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	else
	{
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);

			
		
		if (nullptr != StructureResult)
		{
			AStructure* NewResult = dynamic_cast<AStructure*>(StructureResult);

			SetActorLocation(PrevPos);

			float NewX = NewResult->Pos.X - GetActorLocation().X ;
			float NewY = NewResult->Pos.Y - GetActorLocation().Y;
			if (abs(NewX) >= abs(NewY))
			{
				RandomDir.X *= (-1.0f);
			}
			else if (abs(NewX) == abs(NewY))
			{
				RandomDir.Y *= (-1.0f);
			}
			else
			{
				RandomDir.Y *= (-1.0f);
			}
		}

		AddActorLocation(RandomDir * _DeltaTime * Speed);
	}

	if (0.0f < RandomDir.X)
	{
		MonsterRenderer->ChangeAnimation("Move_Dip_Right");
	}

	else
	{
		MonsterRenderer->ChangeAnimation("Move_Dip_Left");
	}

	if (DelayTime > 1.0f)
	{
		DirChange();
		DelayTime = 0.0f;
	}

	if (this->Hp <= 0.0f)
	{
		DieStart();
	}
}

void ADip::DirChange()
{

	if (0.0f < RandomDir.X)
	{
		MonsterRenderer->ChangeAnimation("Idle_Dip_Right");
	}

	else
	{
		MonsterRenderer->ChangeAnimation("Idle_Dip_Left");
	}

	float XValue = Random.Randomfloat(-0.5f, 0.5f);
	float YValue = Random.Randomfloat(-0.5f, 0.5f);
	if (0.0f > XValue)
	{
		XValue -= 0.25f;
	}
	else
	{
		XValue += 0.25f;
	}
	if (0.0f > YValue)
	{
		YValue -= 0.25f;
	}
	else
	{
		YValue += 0.25f;
	}

	RandomDir = { XValue ,YValue };

	RandomDir.Normalize();

	FSM.ChangeState(DipState::IdleRight);
}


void ADip::DieStart()
{
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	PlayGameMode->CurRoom->MonsterNumber--;
	DelayTime = 0.0f;
	CollisionComponent->SetActive(false);
	ShadowRenderer->SetSpriteScale(0.0f);
	int RandomValue = Random.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		EffectPlayer = UEngineSound::Play("death burst small.wav");
		break;
	case 2:
		EffectPlayer = UEngineSound::Play("death burst small 2.wav");
		break;
	default:
		EffectPlayer = UEngineSound::Play("death burst small 3.wav");
		break;
	}
	FSM.ChangeState(DipState::Die);
}

void ADip::Die(float _DeltaTime)
{

	DelayTime += _DeltaTime;

	if (DelayTime > 1.1f)
	{
		Destroy();
	}
}
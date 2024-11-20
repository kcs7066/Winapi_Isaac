#include "PreCompile.h"
#include "Isaac.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "Tear.h"
#include "ContentsEnum.h"
#include "PlayGameMode.h"
#include "Bomb.h"
#include "TheInnerEye.h"

AIsaac::AIsaac()
{
	SetActorLocation({ 0, 0 });
	{
		ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShadowRenderer->SetOrder(ERenderOrder::SHADOW);
		ShadowRenderer->SetSprite("Shadow.png");
		ShadowRenderer->SetSpriteScale(0.3f);
	}


	{
		BodyRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BodyRenderer->SetOrder(ERenderOrder::PLAYER);
		BodyRenderer->SetComponentScale({ 70, 70 });
		BodyRenderer->SetComponentLocation({ 0,-10 });
		BodyRenderer->CreateAnimation("Idle_Body", "Body.png", 29, 29, 0.1f);
		BodyRenderer->CreateAnimation("Run_RightBody", "Body.png", 10, 19, 0.1f);
		BodyRenderer->CreateAnimation("Run_DownBody", "Body.png", 20, 29, 0.1f);
		BodyRenderer->CreateAnimation("Run_LeftBody", "Body.png", 0, 9, 0.1f);
		BodyRenderer->CreateAnimation("Item_Body", "Character_IsaacItem.png", 3, 3, 0.1f);
	}

	

	{
		HeadRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HeadRenderer->SetOrder(ERenderOrder::PLAYER);
		HeadRenderer->SetComponentScale({ 70, 70 });
		HeadRenderer->SetComponentLocation({ 0,-40 });


		HeadRenderer->CreateAnimation("Idle_Head", "Head.png", 7, 7, 0.1f);
		HeadRenderer->CreateAnimation("Attack_UpHead", "Head.png", {  4, 5 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Attack_RightHead", "Head.png", { 2, 3 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Attack_DownHead", "Head.png", { 6, 7 }, { 0.1f,0.4f});
		HeadRenderer->CreateAnimation("Attack_LeftHead", "Head.png", { 0, 1 }, { 0.1f,0.4f });
		HeadRenderer->CreateAnimation("Run_UpHead", "Head.png", 5, 5, 0.1f);
		HeadRenderer->CreateAnimation("Run_RightHead", "Head.png", 3, 3, 0.1f);
		HeadRenderer->CreateAnimation("Run_LeftHead", "Head.png", 1, 1, 0.1f);
		HeadRenderer->CreateAnimation("Item_Head", "Character_IsaacItem.png", 0, 0, 0.1f);
	}

	HitRenderer = CreateDefaultSubObject<USpriteRenderer>();
	HitRenderer->SetOrder(ERenderOrder::PLAYER);
	HitRenderer->SetComponentScale({ 130, 130 });
	HitRenderer->SetComponentLocation({ 10,-30 });
	HitRenderer->CreateAnimation("Hit_Isaac", "Character_Isaac.png", 0, 0, 0.1f);
	HitRenderer->CreateAnimation("None", "Character_Isaac.png", 14, 14, 0.1f);
	HitRenderer->ChangeAnimation("None");

	ItemRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemRenderer->SetOrder(ERenderOrder::PLAYER);
	ItemRenderer->SetSprite("Item_TheInnerEye.png");
	ItemRenderer->SetSpriteScale(0.0f);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 35, 35 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Player);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);


	//GetWorld()->CollisionGroupLink(ECollisionGroup::Player, ECollisionGroup::Monster);
	//GetWorld()->CollisionGroupLink(ECollisionGroup::Monster, ECollisionGroup::Player);


	//CollisionComponent->SetCollisionEnter(std::bind(&AIsaac::CollisionEnter, this, std::placeholders::_1));
	//CollisionComponent->SetCollisionStay(std::bind(&AIsaac::CollisionStay, this, std::placeholders::_1));
	//CollisionComponent->SetCollisionEnd(std::bind(&AIsaac::CollisionEnd, this, std::placeholders::_1));

	DebugOn();
}

//void AIsaac::CollisionEnter(AActor* _ColActor)
//{
//	int a = 0;
//}
//
//void AIsaac::CollisionStay(AActor* _ColActor)
//{
//	int a = 0;
//}
//
//void AIsaac::CollisionEnd(AActor* _ColActor)
//{
//	int  a = 0;
//}

AIsaac::~AIsaac()
{
}

void AIsaac::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SetCameraToMainPawn(false);
	
	//BGMPlayer = UEngineSound::Play("title screen.ogg");
	
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
	
	FSM.CreateState(IsaacState::Idle, std::bind(&AIsaac::Idle, this, std::placeholders::_1),
		[this]()
		{  
			HitRenderer->SetComponentScale({ 0, 0 });
			HeadRenderer->ChangeAnimation("Idle_Head");
			HeadRenderer->SetComponentScale({ 70, 70 });
			BodyRenderer->ChangeAnimation("Idle_Body");
			BodyRenderer->SetComponentScale({ 70, 70 });
		}
	);

	FSM.CreateState(IsaacState::Move, std::bind(&AIsaac::Move, this, std::placeholders::_1),
		[this]()
		{
			HeadRenderer->ChangeAnimation("Idle_Head");
			BodyRenderer->ChangeAnimation("Run_DownBody");
		}
	);

	FSM.CreateState(IsaacState::Attack, std::bind(&AIsaac::Attack, this, std::placeholders::_1),
		[this]()
		{
		}
	);

	FSM.CreateState(IsaacState::Hit, std::bind(&AIsaac::Hit, this, std::placeholders::_1),
		[this]()
		{
			//CollisionComponent->SetActive(false);
			HeadRenderer->SetComponentScale({ 0, 0 });
			BodyRenderer->SetComponentScale({ 0, 0 });
			HitRenderer->ChangeAnimation("Hit_Isaac");
			HitRenderer->SetComponentScale({ 130, 130 });
		}
	);

	FSM.CreateState(IsaacState::Item, std::bind(&AIsaac::Item, this, std::placeholders::_1),
		[this]()
		{
			//CollisionComponent->SetActive(false);
			HeadRenderer->ChangeAnimation("Item_Head");
			BodyRenderer->ChangeAnimation("Item_Body");
		}
	);

	FSM.CreateState(IsaacState::Die, std::bind(&AIsaac::Die, this, std::placeholders::_1),
		[this]()
		{
			CollisionComponent->SetActive(false);
			HeadRenderer->Destroy();
			BodyRenderer->Destroy();
			ShadowRenderer->Destroy();
			DeathRenderer->ChangeAnimation("Death_Isaac");
		}
	);

	FSM.ChangeState(IsaacState::Idle);
}

void AIsaac::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	
		UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
		UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

		APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

		if (true == UEngineInput::GetInst().IsPress(VK_NUMPAD0))
		{
			BombNumber = 99;

			PlayGameMode->BombUi->SetValue(BombNumber);
		}

		if (true == UEngineInput::GetInst().IsPress('E'))
		{
			if (BombNumber > 0)
			{
				if (BombCoolTime <= 0.0f)
				{
					ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>();
					NewBomb->SetActorLocation(GetActorLocation());
					BombCoolTime = 1.3f;

					BombNumber--;
					PlayGameMode->BombUi->SetValue(BombNumber);
				}
			}
		}

		BulletCoolTime -= _DeltaTime;
		BombCoolTime -= _DeltaTime;
		HitCoolTime -= _DeltaTime;
		FSM.Update(_DeltaTime);
		
}



void AIsaac::Idle(float _DeltaTime)
{
	HpCheck();
	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(IsaacState::Move);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_UP))
	{
		FSM.ChangeState(IsaacState::Attack);
	}


	if (true == UEngineInput::GetInst().IsPress(VK_RIGHT))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_DOWN))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_LEFT))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	AActor* MonsterResult = CollisionComponent->CollisionOnce(ECollisionGroup::Monster);
	if (nullptr != MonsterResult)
	{
		if (0.0f >= HitCoolTime)
		{
			Hp--;
			HitStart();
		}
	}
}




void AIsaac::Move(float _DeltaTime)
{
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();

	HpCheck();

	if (true == UEngineInput::GetInst().IsPress(VK_UP))
	{
		FSM.ChangeState(IsaacState::Attack);
	}


	if (true == UEngineInput::GetInst().IsPress(VK_RIGHT))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_DOWN))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_LEFT))
	{
		FSM.ChangeState(IsaacState::Attack);
	}

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		HeadRenderer->ChangeAnimation("Run_RightHead");
		BodyRenderer->ChangeAnimation("Run_RightBody");
		Vector += FVector2D::RIGHT;
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		HeadRenderer->ChangeAnimation("Run_LeftHead");
		BodyRenderer->ChangeAnimation("Run_LeftBody");
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		HeadRenderer->ChangeAnimation("Idle_Head");
		BodyRenderer->ChangeAnimation("Run_DownBody");
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		HeadRenderer->ChangeAnimation("Run_UpHead");
		BodyRenderer->ChangeAnimation("Run_DownBody");
		Vector += FVector2D::UP;
	}

	Vector.Normalize();

	if (true == PlayGameMode->CurRoom->RoomClear)
	{

		if (true == CanMove)
		{
			AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Door);



			if (nullptr != Result)
			{
				CanMove = false;
				ADoor* NewResult = dynamic_cast<ADoor*>(Result);
				PlayGameMode->CurRoom = NewResult->LinkedRoom;


				switch (NewResult->Dir)
				{
				case DoorDir::UP:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y + 104.0f });
					break;
				case DoorDir::RIGHT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X - 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;
				case DoorDir::DOWN:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y - 104.0f });
					break;
				case DoorDir::LEFT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;

				default:
					break;
				}
				
				FSM.ChangeState(IsaacState::Idle);
			}
		}
	}
		
	AActor* ItemResult = CollisionComponent->CollisionOnce(ECollisionGroup::Item);
	if (nullptr != ItemResult)
	{
		AItem* NewItem = dynamic_cast<AItem*>(ItemResult);
		ItemStart(NewItem);
	}
	

	FVector2D Location = GetActorLocation() += Vector * _DeltaTime * Speed;

	if 
		(
		PlayGameMode->CurRoom->RoomPos.X - Location.X > 338.0f ||
		PlayGameMode->CurRoom->RoomPos.X - Location.X < -338.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - Location.Y > 182.0f ||
		PlayGameMode->CurRoom->RoomPos.Y - Location.Y < -182.0f
			)
	{
	}
	
	else
	{

		PrevPos = GetActorLocation();
		if (true == CanMove) {
			AddActorLocation(Vector * _DeltaTime * Speed);
		}
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);


		if (nullptr != StructureResult)
		{
			SetActorLocation(PrevPos);
		}

	}


	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(IsaacState::Idle);

	}

	AActor* MonsterResult = CollisionComponent->CollisionOnce(ECollisionGroup::Monster);
	if (nullptr != MonsterResult)
	{
		if (0.0f >= HitCoolTime)
		{
			Hp--;
			HitStart();
		}
	}

}

void AIsaac::Attack(float _DeltaTime)
{

	if (BulletCoolTime < 0.0f)
	{
		if (true == UEngineInput::GetInst().IsPress(VK_UP))
		{
			ATear* NewTear = GetWorld()->SpawnActor<ATear>();
			NewTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
			if (true == TheInnerEyeValue)
			{
				ATear* NewSecondTear = GetWorld()->SpawnActor<ATear>();
				ATear* NewThirdTear = GetWorld()->SpawnActor<ATear>();

				NewSecondTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				NewThirdTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				FVector2D SecondDir = { 1,-7 };
				FVector2D ThirdDir = { -1,-7 };
				SecondDir.Normalize();
				ThirdDir.Normalize();
				NewSecondTear->Dir = SecondDir;
				NewThirdTear->Dir = ThirdDir;
			}
			else
			{
			}
			NewTear->Dir = FVector2D::UP;
			HeadRenderer->ChangeAnimation("Attack_UpHead");
		}


		if (true == UEngineInput::GetInst().IsPress(VK_RIGHT))
		{
			ATear* NewTear = GetWorld()->SpawnActor<ATear>();
			NewTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
			if (true == TheInnerEyeValue)
			{
				ATear* NewSecondTear = GetWorld()->SpawnActor<ATear>();
				ATear* NewThirdTear = GetWorld()->SpawnActor<ATear>();
				NewSecondTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				NewThirdTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				FVector2D SecondDir = { 7,1 };
				FVector2D ThirdDir = { 7,-1 };
				SecondDir.Normalize();
				ThirdDir.Normalize();
				NewSecondTear->Dir = SecondDir;
				NewThirdTear->Dir = ThirdDir;
			}
			else
			{
			}
			NewTear->Dir = FVector2D::RIGHT;
			HeadRenderer->ChangeAnimation("Attack_RightHead");
		}

		if (true == UEngineInput::GetInst().IsPress(VK_DOWN))
		{
			ATear* NewTear = GetWorld()->SpawnActor<ATear>();
			NewTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
			if (true == TheInnerEyeValue)
			{
				ATear* NewSecondTear = GetWorld()->SpawnActor<ATear>();
				ATear* NewThirdTear = GetWorld()->SpawnActor<ATear>();
				NewSecondTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				NewThirdTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				FVector2D SecondDir = { 1,7 };
				FVector2D ThirdDir = { -1,7 };
				SecondDir.Normalize();
				ThirdDir.Normalize();
				NewSecondTear->Dir = SecondDir;
				NewThirdTear->Dir = ThirdDir;
			}
			else
			{
			}
			NewTear->Dir = FVector2D::DOWN;
			HeadRenderer->ChangeAnimation("Attack_DownHead");
		}

		if (true == UEngineInput::GetInst().IsPress(VK_LEFT))
		{
			ATear* NewTear = GetWorld()->SpawnActor<ATear>();
			NewTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
			if (true == TheInnerEyeValue)
			{
				ATear* NewSecondTear = GetWorld()->SpawnActor<ATear>();
				ATear* NewThirdTear = GetWorld()->SpawnActor<ATear>();
				NewSecondTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				NewThirdTear->SetActorLocation(GetWorld()->GetPawn()->GetActorLocation());
				FVector2D SecondDir = { -7,1 };
				FVector2D ThirdDir = { -7,-1 };
				SecondDir.Normalize();
				ThirdDir.Normalize();
				NewSecondTear->Dir = SecondDir;
				NewThirdTear->Dir = ThirdDir;
			}
			else
			{
			}
			NewTear->Dir = FVector2D::LEFT;
			HeadRenderer->ChangeAnimation("Attack_LeftHead");
		}

		//switch (_Value)
		//{
		//case VK_UP:

		//	
		//	break;
		//case VK_RIGHT:

		//	break;

		//case VK_DOWN:
		//	
		//	break;

		//case VK_LEFT:
		//	
		//	break;

		//default:
		//	break;
		//}
		BulletCoolTime = 0.5f;
	}

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
		BodyRenderer->ChangeAnimation("Run_RightBody");
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
		BodyRenderer->ChangeAnimation("Run_LeftBody");
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
		BodyRenderer->ChangeAnimation("Run_DownBody");
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
		BodyRenderer->ChangeAnimation("Run_DownBody");
	}

	if (false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('S') &&
		false == UEngineInput::GetInst().IsPress('D'))
	{
		BodyRenderer->ChangeAnimation("Idle_Body");
	}

	Vector.Normalize();
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	if (true == PlayGameMode->CurRoom->RoomClear)
	{

		if (true == CanMove)
		{
			AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Door);



			if (nullptr != Result)
			{
				CanMove = false;
				ADoor* NewResult = dynamic_cast<ADoor*>(Result);
				PlayGameMode->CurRoom = NewResult->LinkedRoom;


				switch (NewResult->Dir)
				{
				case DoorDir::UP:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y + 104.0f });
					break;
				case DoorDir::RIGHT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X - 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;
				case DoorDir::DOWN:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y - 104.0f });
					break;
				case DoorDir::LEFT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;

				default:
					break;
				}

			}
		}
	}



	FVector2D Location = GetActorLocation() += Vector * _DeltaTime * Speed;

	if
		(
			PlayGameMode->CurRoom->RoomPos.X - Location.X > 338.0f ||
			PlayGameMode->CurRoom->RoomPos.X - Location.X < -338.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y > 182.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y < -182.0f
			)
	{
	}

	else
	{

		PrevPos = GetActorLocation();
		if (true == CanMove) {
			AddActorLocation(Vector * _DeltaTime * Speed);
		}
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);


		if (nullptr != StructureResult)
		{
			SetActorLocation(PrevPos);
		}

	}

	if (false == UEngineInput::GetInst().IsPress(VK_UP) &&
		false == UEngineInput::GetInst().IsPress(VK_RIGHT) &&
		false == UEngineInput::GetInst().IsPress(VK_DOWN) &&
		false == UEngineInput::GetInst().IsPress(VK_LEFT))
	{
		FSM.ChangeState(IsaacState::Idle);

	}
}

void AIsaac::HitStart()
{
	DelayTime = 0.0f;
	HitCoolTime = 1.0f;
	FSM.ChangeState(IsaacState::Hit);
}

void AIsaac::Hit(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
	}

	Vector.Normalize();
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	if (true == PlayGameMode->CurRoom->RoomClear)
	{

		if (true == CanMove)
		{
			AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Door);



			if (nullptr != Result)
			{
				CanMove = false;
				ADoor* NewResult = dynamic_cast<ADoor*>(Result);
				PlayGameMode->CurRoom = NewResult->LinkedRoom;


				switch (NewResult->Dir)
				{
				case DoorDir::UP:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y + 104.0f });
					break;
				case DoorDir::RIGHT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X - 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;
				case DoorDir::DOWN:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X,PlayGameMode->CurRoom->RoomPos.Y - 104.0f });
					break;
				case DoorDir::LEFT:
					this->SetActorLocation({ PlayGameMode->CurRoom->RoomPos.X + 312.f,PlayGameMode->CurRoom->RoomPos.Y });
					break;

				default:
					break;
				}

			}
		}
	}



	FVector2D Location = GetActorLocation() += Vector * _DeltaTime * Speed;

	if
		(
			PlayGameMode->CurRoom->RoomPos.X - Location.X > 338.0f ||
			PlayGameMode->CurRoom->RoomPos.X - Location.X < -338.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y > 182.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y < -182.0f
			)
	{
	}

	else
	{

		PrevPos = GetActorLocation();
		if (true == CanMove) {
			AddActorLocation(Vector * _DeltaTime * Speed);
		}
		AActor* StructureResult = CollisionComponent->CollisionOnce(ECollisionGroup::Structure);


		if (nullptr != StructureResult)
		{
			SetActorLocation(PrevPos);
		}

	}
	if (0.3f <= DelayTime)
	{

		FSM.ChangeState(IsaacState::Idle);
	}
}

void AIsaac::ItemStart(AItem* _Item)
{
	ATheInnerEye* NewTheInnerEye = dynamic_cast<ATheInnerEye*>(_Item);
	if (nullptr != NewTheInnerEye)
	{
		TheInnerEyeValue = true;
		_Item->ItemRenderer->Destroy();
		_Item->CollisionComponent->SetActive(false);
	}

	DelayTime = 0.0f;
	FSM.ChangeState(IsaacState::Item);
}
void AIsaac::Item(float _DeltaTime)
{
	DelayTime += _DeltaTime;

	if (true == TheInnerEyeValue)
	{
		ItemRenderer->SetSpriteScale(2.0f);
		ItemRenderer->SetComponentLocation({ 0,-90 });
	}

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
	}

	Vector.Normalize();

	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	FVector2D Location = GetActorLocation() += Vector * _DeltaTime * Speed;

	if
		(
			PlayGameMode->CurRoom->RoomPos.X - Location.X > 338.0f ||
			PlayGameMode->CurRoom->RoomPos.X - Location.X < -338.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y > 182.0f ||
			PlayGameMode->CurRoom->RoomPos.Y - Location.Y < -182.0f
			)
	{ }
	else
	{

		AddActorLocation(Vector * _DeltaTime * Speed);
	}

	if (1.0 <= DelayTime)
	{

		ItemRenderer->SetSpriteScale(0.0f);
		FSM.ChangeState(IsaacState::Move);
	}
}

void AIsaac::Die(float _DeltaTime)
{
	GhostPos -= _DeltaTime * 200.0f;
	GhostRenderer->SetComponentLocation({ 20.0f,GhostPos });

}

void AIsaac::DieStart()
{
	DeathRenderer = CreateDefaultSubObject<USpriteRenderer>();
	DeathRenderer->SetOrder(ERenderOrder::PLAYER);
	DeathRenderer->SetComponentScale({ 130, 130 });
	DeathRenderer->SetComponentLocation({ 20,-15 });
	DeathRenderer->CreateAnimation("Death_Isaac", "Character_Isaac.png", { 2, 1 }, { 0.2f,9999.0f });
	DeathRenderer->ChangeAnimation("Death_Isaac");

	GhostRenderer = CreateDefaultSubObject<USpriteRenderer>();
	GhostRenderer->SetOrder(ERenderOrder::PLAYER);
	GhostRenderer->SetComponentScale({ 130, 130 });
	GhostRenderer->SetComponentLocation({ 20,-15 });
	GhostRenderer->CreateAnimation("Ghost", "Ghost.png", 0, 4 , 0.1f);
	GhostRenderer->ChangeAnimation("Ghost");

	FSM.ChangeState(IsaacState::Die);
}

void AIsaac::LevelChangeStart()
{
	int a = 0;
}

void AIsaac::HpCheck()
{
	APlayGameMode* PlayGameMode = GetWorld()->GetGameMode<APlayGameMode>();
	switch (Hp)
	{

	case 6:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		break;

	case 5:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Half_Heart");
		break;

	case 4:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		break;

	case 3:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Half_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		break;

	case 2:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		break;

	case 1:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Half_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		break;

	case 0:
	case -1:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Empty_Heart");
		DieStart();
		break;

	default:
		PlayGameMode->HeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->SecondHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		PlayGameMode->ThirdHeartUi->HUDRenderer->ChangeAnimation("Full_Heart");
		break;
	}
}
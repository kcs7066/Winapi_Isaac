#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class NewPlayerState
{
	Idle,
	Move
	
	
};

// Ό³Έν :
class AIsaac : public AActor
{
public:
	// constrcuter destructer
	AIsaac();
	~AIsaac();

	// delete Function
	AIsaac(const AIsaac& _Other) = delete;
	AIsaac(AIsaac&& _Other) noexcept = delete;
	AIsaac& operator=(const AIsaac& _Other) = delete;
	AIsaac& operator=(AIsaac&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart() override;

	//void Idle(float _DeltaTime);
	//void Move(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);


    void Attack(FVector2D _Dir);

	class USpriteRenderer* HeadRenderer = nullptr;
	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	void DirCheck();

protected:

private:
	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	
	std::string DirString = "_Right";

	class USpriteRenderer* BodyRenderer = nullptr;
	UFSMStateManager FSM = UFSMStateManager();
	int Test = 0;
	float BulletCoolTime = 0.5f;
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "EnemyBase.generated.h"

class UEnemyStateComponent;
class UEnemyStatusComponent;
class UEnemyAnimComponent;
class UWidgetComponent;
class UBehaviorTree;

UCLASS()
class MAINPROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UEnemyStateComponent* GetStateComponent();

public:
	virtual void Attack();
	virtual void Death();

protected :
	void SetNameTag(FString InName);
	void UpdateHealthPoint();

private:
	void InitStatus();
	void InitWidgets();

public :
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* NameTagWidget;

	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* HPWidget;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyAnimComponent* Animation;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;
};

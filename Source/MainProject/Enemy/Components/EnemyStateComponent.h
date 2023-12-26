#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStateComponent.generated.h"

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	Idle,
	Approach,
	Action,
	Patrol,
	Hitted,
	Stunned,
	Avoid,
	Death,
	Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyStateTypeChanged, EEnemyStateType, InPrevType, EEnemyStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UEnemyStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyStateComponent();

protected:
	virtual void BeginPlay() override;

public : 
	FORCEINLINE EEnemyStateType GetEnemyState() { return Type; }

public :
	FORCEINLINE bool IsIdleMode() { return Type == EEnemyStateType::Idle; }
	FORCEINLINE bool IsApproachMode() { return Type == EEnemyStateType::Approach; }
	FORCEINLINE bool IsActionMode() { return Type == EEnemyStateType::Action; }
	FORCEINLINE bool IsPatrolMode() { return Type == EEnemyStateType::Patrol; }
	FORCEINLINE bool IsHittedMode() { return Type == EEnemyStateType::Hitted; }
	FORCEINLINE bool IsStunnedMode() { return Type == EEnemyStateType::Stunned; }
	FORCEINLINE bool IsAvoidMode() { return Type == EEnemyStateType::Avoid; }
	FORCEINLINE bool IsDeathMode() { return Type == EEnemyStateType::Death; }

public :
	void SetIdleMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetStunnedMode();
	void SetAvoidMode();
	void SetDeathMode();
	
public :
	UPROPERTY(BlueprintAssignable)
		FEnemyStateTypeChanged OnEnemyStateTypeChanged;

private :
	void ChangeType(EEnemyStateType InType);

private :
	EEnemyStateType Type;

};

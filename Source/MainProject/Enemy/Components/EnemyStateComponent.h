#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStateComponent.generated.h"

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	Idle,
	Action,
	Hitted,
	Stunned,
	Death,
	Max
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
	FORCEINLINE bool IsIdleMode() { return Type == EEnemyStateType::Idle; }
	FORCEINLINE bool IsActionMode() { return Type == EEnemyStateType::Action; }
	FORCEINLINE bool IsHittedMode() { return Type == EEnemyStateType::Hitted; }
	FORCEINLINE bool IsStunnedMode() { return Type == EEnemyStateType::Stunned; }

public :
	void SetIdleMode();
	void SetActionMode();
	void SetHittedMode();
	void SetStunnedMode();
	
public :
	UPROPERTY(BlueprintAssignable)
		FEnemyStateTypeChanged OnEnemyStateTypeChanged;

private :
	void ChangeType(EEnemyStateType InType);

private :
	EEnemyStateType Type;

};

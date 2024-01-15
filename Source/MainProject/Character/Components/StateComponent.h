#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle,
	Attack,
	DoubleAttack,
	UltimateMode,
	Ultimate,
	ChargeBlastMode,
	ChargeBlast,
	GrenadeMode,
	Grenade,
	Dive_Forward,
	Dive_Backward,
	Dive_Left,
	Dive_Right,
	Hitted,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public :
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	UFUNCTION(BlueprintPure)
		bool IsDiveMode();

public :
	void SetIdleMode();
	void SetAttackMode();
	void SetDoubleAttackMode();
	void SetUltimateMode();
	void SetChargeBlastMode();
	void SetGrenadeMode();
	void SetDiveMode(EStateType InType);

public :
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;

private :
	void ChangeType(EStateType InType);

private :
	EStateType Type;

};

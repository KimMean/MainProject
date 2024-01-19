#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

UENUM(BlueprintType)
enum class EActionMode : uint8
{
	NormalMode,
	UltimateMode,
	ChargeBlastMode,
	GrenadeMode,
	Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionModeChanged, EActionMode, InPrevMode, EActionMode, InNewMode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public :
	FORCEINLINE float GetBaseArmLength() { return BaseArmLength; }
	FORCEINLINE float GetAimModeArmLength() { return AimModeArmLength; }

	FORCEINLINE bool GetAimMode() { return bAimMode; }
	FORCEINLINE void SetAimMode(bool InAimMode) { bAimMode = InAimMode; }

	FORCEINLINE float GetInAir() { return bInAir; }
	FORCEINLINE void SetInAir(bool IsAir) { bInAir = IsAir; }

	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() { return RunSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

	FORCEINLINE bool GetAttack() { return bAttack; }
	FORCEINLINE void SetAttack(bool InAttack) { bAttack = InAttack; }
	FORCEINLINE bool GetComboAttack() { return bComboAttack; }
	FORCEINLINE void SetComboAttack(bool InComboAttack) { bComboAttack = InComboAttack; }
	FORCEINLINE bool GetEnableCombo() { return bEnableCombo; }
	FORCEINLINE void SetEnableCombo(bool InEnableCombo) { bEnableCombo = InEnableCombo; }

	FORCEINLINE bool IsCanMove() { return bCanMove; }
	FORCEINLINE bool GetIsAvoid() { return bIsAvoid; }
	FORCEINLINE void SetIsAvoid(bool InAvoid) { bIsAvoid = InAvoid; }

	FORCEINLINE EActionMode GetActionMode() { return ActionMode; }

public :
	float GetMaxHealthPoint();
	float GetCurHealthPoint();
	void AdjustHealthPoint(float InAdjustValue);

public:
	void ChangeActionMode(EActionMode InMode);

public:
	UPROPERTY(BlueprintAssignable)
		FActionModeChanged OnActionModeChanged;


private :
	UPROPERTY(VisibleDefaultsOnly, Category = "SpringArm")
		float BaseArmLength = 200.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "SpringArm")
		float AimModeArmLength = 100.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "AimMode")
		bool bAimMode = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "Speed")
		bool bInAir = false;
	UPROPERTY(VisibleDefaultsOnly, Category = "Speed")
		float WalkSpeed = 300.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Speed")
		float RunSpeed = 600.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Speed")
		float SprintSpeed = 800.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Attack")
		bool bAttack = false;
	UPROPERTY(VisibleDefaultsOnly, Category = "Attack")
		bool bComboAttack = false;
	UPROPERTY(VisibleDefaultsOnly, Category = "Attack")
		bool bEnableCombo = false;

	UPROPERTY(VisibleDefaultsOnly, Category = "CanMove")
		bool bCanMove = true;

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
		float MaxHealth;
	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
		float CurHealth;

	UPROPERTY(VisibleDefaultsOnly, Category = "Avoid")
		bool bIsAvoid;

	EActionMode ActionMode;
};

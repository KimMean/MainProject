#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


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


private :
	UPROPERTY(EditDefaultsOnly, Category = "SpringArm")
		float BaseArmLength = 300.0f;
	UPROPERTY(EditDefaultsOnly, Category = "SpringArm")
		float AimModeArmLength = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AimMode")
		bool bAimMode = false;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		bool bInAir = false;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float WalkSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float RunSpeed = 400.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float SprintSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		bool bAttack = false;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		bool bComboAttack = false;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		bool bEnableCombo = false;

	UPROPERTY(EditDefaultsOnly, Category = "CanMove")
		bool bCanMove = true;


};

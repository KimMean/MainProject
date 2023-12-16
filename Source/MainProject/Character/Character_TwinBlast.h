#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Components/StateComponent.h"
#include "Character_TwinBlast.generated.h"

UCLASS()
class MAINPROJECT_API ACharacter_TwinBlast : public ACharacter
{
	GENERATED_BODY()
	
public :
	ACharacter_TwinBlast(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public :
	class UStatusComponent* GetStatus() { return Status; }

public:
	void Begin_DoubleCombo();
	void End_DoubleShot();

	void Firing(const USkeletalMeshSocket* InSocket);
	void BulletFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam);
	void ChargeBoltFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam);
	void GrenadeFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam);
	void EndAttackMode();

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

	void OnJump();
	void OnAttack();
	void OnWalkMode();
	void OnJogMode();
	void OnSprintMode();

	void OnAvoid();

	void OnNormalMode();
	void OffNormalMode();
	void OnUltimateMode();
	void OffUltimateMode();
	void OnChargeBlastMode();
	void OffChargeBlastMode();
	void OnGrenadeMode();
	void OffGrenadeMode();

private :
	void Attack_DoubleShot();
	void Attack_Ultimate();
	void Attack_ChargeBlast();
	void Attack_Grenade();

	void Begin_Roll();
	void End_Roll();




private :
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void OnActionModeChanged(EActionMode InPrevType, EActionMode InNewType);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UAnimationComponent* Animation;

	UPROPERTY(VisibleDefaultsOnly)
		class UStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UStateComponent* State;


private :
	class TSubclassOf<class UMainWidget> MainWidgetClass;
	class UMainWidget* MainWidget;

private :
	class TSubclassOf<class ABullet> Bullet;
	class TSubclassOf<class AChargeBolt> ChargeBolt;
	class TSubclassOf<class AGrenade> Grenade;
};

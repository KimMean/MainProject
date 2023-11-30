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
	ACharacter_TwinBlast();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Begin_DoubleCombo();
	void End_DoubleShot();

	void BulletFiring(const USkeletalMeshSocket* socket);

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

	void OnAimMode();
	void OffAimMode();

private :
	void Begin_DoubleShot();

	void Begin_Roll();
	void End_Roll();




private :
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

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
};

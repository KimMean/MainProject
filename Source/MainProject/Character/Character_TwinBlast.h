#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

public :
	FORCEINLINE bool GetAimMode() { return bAimMode; }

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

	void OnWalkMode();
	void OnJogMode();
	void OnSprintMode();

	void OnAimMode();
	void OffAimMode();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;


private :
	class TSubclassOf<class UMainWidget> MainWidgetClass;
	class UMainWidget* MainWidget;

private :
	float WalkSpeed = 200.0f;
	float JogSpeed = 400.0f;
	float SprintSpeed = 600.0f;

	float BaseArmLength = 300.0f;
	float AimModeArmLength = 100.0f;

	bool bAimMode = false;
};

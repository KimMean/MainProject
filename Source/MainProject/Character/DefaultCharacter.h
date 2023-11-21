
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

UCLASS()
class MAINPROJECT_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADefaultCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;
};

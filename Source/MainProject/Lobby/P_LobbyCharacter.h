#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P_LobbyCharacter.generated.h"

UCLASS()
class MAINPROJECT_API AP_LobbyCharacter : public APawn
{
	GENERATED_BODY()

public:
	AP_LobbyCharacter();

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* CapsuleComponent;

	//UPROPERTY(VisibleDefaultsOnly)
	//	class USpringArmComponent* SpringArm;
	//
	//UPROPERTY(VisibleDefaultsOnly)
	//	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;
};

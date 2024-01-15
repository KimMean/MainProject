#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Components/StatusComponent.h"
#include "Character/Components/InverseKinematicsComponent.h"
#include "TwinBlastAnimInstance.generated.h"

UCLASS()
class MAINPROJECT_API UTwinBlastAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere, replicated)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, replicated)
		float Direction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, replicated)
		float AimHorizontal;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, replicated)
		float AimVertical;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FIKData IKData;

private :
	UFUNCTION()
		void OnActionModeChanged(EActionMode InPrevType, EActionMode InNewType);

protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EActionMode ActionMode;

private :
	class ACharacter* OwnerCharacter;
	class ACharacter_TwinBlast* TwinBlast;

};

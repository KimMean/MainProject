#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Components/StatusComponent.h"
#include "TwinBlastAnimInstance.generated.h"

UCLASS()
class MAINPROJECT_API UTwinBlastAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float AimHorizontal;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float AimVertical;

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

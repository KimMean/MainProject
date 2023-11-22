#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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

private :
	class ACharacter* OwnerCharacter;
};

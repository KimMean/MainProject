#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CorpseAnimInstance.generated.h"

UCLASS()
class MAINPROJECT_API UCorpseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
};

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AEnemyBase;

UCLASS()
class MAINPROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	AEnemyBase* OwnerEnemy;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
};

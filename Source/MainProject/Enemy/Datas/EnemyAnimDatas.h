#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "EnemyAnimDatas.generated.h"

class ACharacter;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FEnemyAnimData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
};

UCLASS()
class MAINPROJECT_API UEnemyAnimDatas : public UDataAsset
{
	GENERATED_BODY()
	
public :
	void BeginPlay(ACharacter InOwnerCharacter);

public :
	FEnemyAnimData* GetAnimationData(EEnemyStateType InEnemyStateType);

protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TMap<EEnemyStateType, FEnemyAnimData> AnimDatas;
};

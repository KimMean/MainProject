#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Components/StateComponent.h"
#include "Engine/DataTable.h"
#include "AnimationComponent.generated.h"

USTRUCT(BlueprintType)
struct FAnimationData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimCompositeBase* Animation;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAnimationComponent();

protected:
	virtual void BeginPlay() override;

public :
	void Attack_DoubleShot();
	void Attack_DoubleShotCombo();
	void Attack_UltimateMode();
	void Attack_Ultimate();
	void Attack_ChargeBlastMode();
	void Attack_ChargeBlast();
	void Attack_GrenadeMode();
	void Attack_Grenade();
	void Dive_Forward();
	void Dive_Backward();
	void Dive_Right();
	void Dive_Left();

private :
	void PlayAnimation(EStateType InState);
	void PlayAnimMontage(EStateType InState);

private :
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

	FAnimationData* Datas[(int32)EStateType::Max];

};

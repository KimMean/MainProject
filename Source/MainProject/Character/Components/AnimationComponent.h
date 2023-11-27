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
	void Play_Roll();

private :
	void PlayAnimation(EStateType InState);

private :
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

	FAnimationData* Datas[(int32)EStateType::Max];

};

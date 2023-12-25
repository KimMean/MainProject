#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "BTTN_PlayAnimation.generated.h"

UCLASS()
class MAINPROJECT_API UBTTN_PlayAnimation : public UBTTaskNode
{
	GENERATED_BODY()
	
public :
	UBTTN_PlayAnimation();

protected :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected :
	UPROPERTY(EditAnywhere)
		EEnemyStateType StateType;
};

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "BTTN_SetSpeed.generated.h"

UCLASS()
class MAINPROJECT_API UBTTN_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public :
	UBTTN_SetSpeed();

protected :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private :
	UPROPERTY(EditAnywhere)
		EEnemySpeedType SpeedType;
};

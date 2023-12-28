#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTN_SetIdleMode.generated.h"

UCLASS()
class MAINPROJECT_API UBTTN_SetIdleMode : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UBTTN_SetIdleMode();

protected :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTN_SetWaitMode.generated.h"

UCLASS()
class MAINPROJECT_API UBTTN_SetWaitMode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTN_SetWaitMode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};

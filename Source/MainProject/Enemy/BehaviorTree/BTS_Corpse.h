#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_Corpse.generated.h"

UCLASS()
class MAINPROJECT_API UBTS_Corpse : public UBTService
{
	GENERATED_BODY()
	
public :
	UBTS_Corpse();

protected :
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

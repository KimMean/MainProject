#include "Enemy/BehaviorTree/Tasks/BTTN_SetSpeed.h"

#include "Enemy/BehaviorComponent.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Components/EnemyStatusComponent.h"

#include "Utilities/DebugLog.h"

UBTTN_SetSpeed::UBTTN_SetSpeed()
{
	NodeName = "SetSpeed";
}

EBTNodeResult::Type UBTTN_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	AEnemyBase* enemy = Cast<AEnemyBase>(controller->GetPawn());
	UEnemyStatusComponent* status = enemy->FindComponentByClass<UEnemyStatusComponent>();

	status->SetSpeed(SpeedType);

	return EBTNodeResult::Succeeded;
}

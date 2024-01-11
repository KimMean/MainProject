#include "Enemy/BehaviorTree/Tasks/BTTN_SetWaitMode.h"

#include "Enemy/EnemyBase.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Components/EnemyStateComponent.h"

UBTTN_SetWaitMode::UBTTN_SetWaitMode()
{
	NodeName = "SetWaitMode";
}

EBTNodeResult::Type UBTTN_SetWaitMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	AEnemyBase* enemy = Cast<AEnemyBase>(controller->GetPawn());
	UEnemyStateComponent* state = enemy->FindComponentByClass<UEnemyStateComponent>();

	state->SetWaitMode();

	return EBTNodeResult::Succeeded;
}

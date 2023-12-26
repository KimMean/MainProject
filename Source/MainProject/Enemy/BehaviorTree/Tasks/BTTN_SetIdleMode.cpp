#include "Enemy/BehaviorTree/Tasks/BTTN_SetIdleMode.h"

#include "Enemy/BehaviorComponent.h"
#include "Enemy/Corpse/Corpse.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Components/EnemyStateComponent.h"

UBTTN_SetIdleMode::UBTTN_SetIdleMode()
{
	NodeName = "SetWaitMode";
}

EBTNodeResult::Type UBTTN_SetIdleMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	ACorpse* enemy = Cast<ACorpse>(controller->GetPawn());
	UEnemyStateComponent* state = enemy->FindComponentByClass<UEnemyStateComponent>();

	state->SetIdleMode();

	return EBTNodeResult::Succeeded;
}

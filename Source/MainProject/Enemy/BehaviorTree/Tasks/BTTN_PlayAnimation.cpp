#include "Enemy/BehaviorTree/Tasks/BTTN_PlayAnimation.h"

#include "Enemy/EnemyBase.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Components/EnemyAnimComponent.h"

#include "Utilities/DebugLog.h"

UBTTN_PlayAnimation::UBTTN_PlayAnimation()
{
	bNotifyTick = true;
	NodeName = "PlayAction";
}

EBTNodeResult::Type UBTTN_PlayAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	AEnemyBase* enemy = Cast<AEnemyBase>(controller->GetPawn());
	UEnemyAnimComponent* animation = enemy->FindComponentByClass<UEnemyAnimComponent>();

	animation->PlayAnimMontage(StateType);

	return EBTNodeResult::InProgress;
}

void UBTTN_PlayAnimation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	AEnemyBase* enemy = Cast<AEnemyBase>(controller->GetPawn());
	UEnemyStateComponent* state = enemy->FindComponentByClass<UEnemyStateComponent>();

	if (state->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

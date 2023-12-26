#include "Enemy/BehaviorTree/Tasks/BTTN_PlayAnimation.h"

#include "Enemy/Corpse/Corpse_AI.h"
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
	ACorpse_AI* ai = Cast<ACorpse_AI>(controller->GetPawn());
	UEnemyAnimComponent* animation = ai->FindComponentByClass<UEnemyAnimComponent>();

	animation->PlayAnimMontage(StateType);

	return EBTNodeResult::InProgress;
}

void UBTTN_PlayAnimation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	ACorpse_AI* ai = Cast<ACorpse_AI>(controller->GetPawn());
	UEnemyStateComponent* state = ai->FindComponentByClass<UEnemyStateComponent>();

	if (state->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

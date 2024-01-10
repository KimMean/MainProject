#include "Enemy/BehaviorTree/BTS_Corpse.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/BehaviorComponent.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "Character/Character_TwinBlast.h"

#include "Utilities/DebugLog.h"

UBTS_Corpse::UBTS_Corpse()
{
	NodeName = "Corpse";
}

void UBTS_Corpse::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemy_AIController* controller = Cast<AEnemy_AIController>(OwnerComp.GetOwner());
	UBehaviorComponent* behavior = controller->FindComponentByClass<UBehaviorComponent>();
	
	AEnemyBase* ai = Cast<AEnemyBase>(controller->GetPawn());
	UEnemyStateComponent* state = ai->FindComponentByClass<UEnemyStateComponent>();
	UEnemyStatusComponent* status = ai->FindComponentByClass<UEnemyStatusComponent>();
	
	ACharacter_TwinBlast* target = behavior->GetTargetPlayer();

	if (state->IsWaitMode()) return;
	if (state->IsActionMode()) return;

	if (!target)	// 플레이어가 범위안에 없음
	{
		state->SetPatrolMode();
		return;
	}

	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetActionRange())	// 공격상태
	{
		state->SetActionMode();
		return;
	}
	if (distance < controller->GetSightRadius())	// 추적 상태
	{
		state->SetApproachMode();
		return;
	}
	if (status->GetIsHitted())
	{
		state->SetApproachMode();
		return;
	}

}

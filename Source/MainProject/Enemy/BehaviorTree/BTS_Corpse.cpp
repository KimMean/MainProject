#include "Enemy/BehaviorTree/BTS_Corpse.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Corpse/Corpse_AI.h"
#include "Enemy/BehaviorComponent.h"
#include "Enemy/Components/EnemyStateComponent.h"
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

	ACorpse_AI* ai = Cast<ACorpse_AI>(controller->GetPawn());
	UEnemyStateComponent* state = ai->FindComponentByClass<UEnemyStateComponent>();

	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	ACharacter_TwinBlast* target = behavior->GetTargetPlayer();

	if (!target)	// �÷��̾ �����ȿ� ����
	{
		//PatrolMode
		behavior->SetPatrolMode();
		return;
	}

	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetActionRange())	// ���ݻ���
	{
		DebugLog::Print("Action Mode");
		behavior->SetActionMode();
		return;
	}
	if (distance < controller->GetSightRadius())	// ���� ����
	{
		DebugLog::Print("Approach Mode");
		behavior->SetApproachMode();
	}
}

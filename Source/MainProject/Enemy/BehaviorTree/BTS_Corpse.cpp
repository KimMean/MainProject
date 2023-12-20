#include "Enemy/BehaviorTree/BTS_Corpse.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Corpse/Corpse_AI.h"
#include "Enemy/BehaviorComponent.h"
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

	ACharacter_TwinBlast* target = behavior->GetTargetPlayer();

	DebugLog::Print("Target??");
	if (!target) return;

	DebugLog::Print("Target On");
	float distance = ai->GetDistanceTo(target);
	if (distance < controller->GetSightRadius())
	{
		DebugLog::Print("ApproachMode");
		behavior->SetApproachMode();
	}
	// state 상태 마다 

}

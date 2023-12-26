#include "Enemy/BehaviorComponent.h"

#include "GameFramework/Character.h"
#include "Character/Character_TwinBlast.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Enemy/Corpse/Corpse.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Utilities/DebugLog.h"

UBehaviorComponent::UBehaviorComponent()
{
}

void UBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	AEnemy_AIController* controller = Cast<AEnemy_AIController>(GetOwner());
	ACorpse* enemy = Cast<ACorpse>(controller->GetPawn());
	DebugLog::Print(enemy->GetName());
	UEnemyStateComponent* state = enemy->FindComponentByClass<UEnemyStateComponent>();
	state->OnEnemyStateTypeChanged.AddDynamic(this, &UBehaviorComponent::OnEnemyStateTypeChanged);
}


ACharacter* UBehaviorComponent::GetTargetCharacter()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(PlayerKey));
}

ACharacter_TwinBlast* UBehaviorComponent::GetTargetPlayer()
{
	return Cast<ACharacter_TwinBlast>(Blackboard->GetValueAsObject(PlayerKey));
}

void UBehaviorComponent::OnEnemyStateTypeChanged(EEnemyStateType InPrevType, EEnemyStateType InNewType)
{
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InNewType);
}



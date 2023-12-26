#include "Enemy/Components/EnemyStateComponent.h"

#include "Utilities/DebugLog.h"

UEnemyStateComponent::UEnemyStateComponent()
{
}


void UEnemyStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyStateComponent::SetIdleMode()
{
	ChangeType(EEnemyStateType::Idle);
}

void UEnemyStateComponent::SetApproachMode()
{
	ChangeType(EEnemyStateType::Approach );
}

void UEnemyStateComponent::SetActionMode()
{
	ChangeType(EEnemyStateType::Action);
}

void UEnemyStateComponent::SetPatrolMode()
{
	ChangeType(EEnemyStateType::Patrol);
}

void UEnemyStateComponent::SetHittedMode()
{
	ChangeType(EEnemyStateType::Hitted);
}

void UEnemyStateComponent::SetStunnedMode()
{
	ChangeType(EEnemyStateType::Stunned);
}

void UEnemyStateComponent::SetAvoidMode()
{
	ChangeType(EEnemyStateType::Avoid);
}

void UEnemyStateComponent::SetDeathMode()
{
	ChangeType(EEnemyStateType::Death);
}

void UEnemyStateComponent::ChangeType(EEnemyStateType InType)
{
	EEnemyStateType type = Type;
	Type = InType;

	if (OnEnemyStateTypeChanged.IsBound())
	{
		OnEnemyStateTypeChanged.Broadcast(type, Type);
	}
}




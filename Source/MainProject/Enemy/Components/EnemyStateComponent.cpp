#include "Enemy/Components/EnemyStateComponent.h"

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

void UEnemyStateComponent::SetActionMode()
{
	ChangeType(EEnemyStateType::Action);
}

void UEnemyStateComponent::SetHittedMode()
{
	ChangeType(EEnemyStateType::Hitted);
}

void UEnemyStateComponent::SetStunnedMode()
{
	ChangeType(EEnemyStateType::Stunned);
}

void UEnemyStateComponent::ChangeType(EEnemyStateType InType)
{
	EEnemyStateType type = Type;
	Type = InType;

	if (OnEnemyStateTypeChanged.IsBound())
		OnEnemyStateTypeChanged.Broadcast(type, Type);
}




#include "Character/Components/StateComponent.h"

UStateComponent::UStateComponent()
{
}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UStateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(type, InType);
}




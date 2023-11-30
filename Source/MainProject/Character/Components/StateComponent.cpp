#include "Character/Components/StateComponent.h"

UStateComponent::UStateComponent()
{
}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UStateComponent::IsDiveMode()
{
	switch (Type)
	{
	case EStateType::Dive_Forward:
	case EStateType::Dive_Backward:
	case EStateType::Dive_Left:
	case EStateType::Dive_Right:
		return true;
	}
	return false;
}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetAttackMode()
{
	ChangeType(EStateType::Attack);
}

void UStateComponent::SetDiveMode(EStateType InType)
{
	ChangeType(InType);
}

void UStateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(type, InType);
}




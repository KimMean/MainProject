#include "Character/Components/StatusComponent.h"

UStatusComponent::UStatusComponent()
{
	MaxHealth = 1000;
	CurHealth = MaxHealth;
}


void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

float UStatusComponent::GetMaxHealthPoint()
{
	return MaxHealth;
}

float UStatusComponent::GetCurHealthPoint()
{
	return CurHealth;
}

void UStatusComponent::AdjustHealthPoint(float InAdjustValue)
{
	CurHealth += InAdjustValue;

	if (CurHealth <= 0)
		CurHealth = 0;

	if (CurHealth > GetMaxHealthPoint())
		CurHealth = GetMaxHealthPoint();
}

void UStatusComponent::ChangeActionMode(EActionMode InMode)
{
	EActionMode mode = ActionMode;
	ActionMode = InMode;

	if (OnActionModeChanged.IsBound())
		OnActionModeChanged.Broadcast(mode, InMode);
}


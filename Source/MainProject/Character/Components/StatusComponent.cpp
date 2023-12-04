#include "Character/Components/StatusComponent.h"

UStatusComponent::UStatusComponent()
{

}


void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusComponent::ChangeActionMode(EActionMode InMode)
{
	EActionMode mode = ActionMode;
	ActionMode = InMode;

	if (OnActionModeChanged.IsBound())
		OnActionModeChanged.Broadcast(mode, InMode);
}


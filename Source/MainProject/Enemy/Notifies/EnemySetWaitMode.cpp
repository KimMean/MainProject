#include "Enemy/Notifies/EnemySetWaitMode.h"

#include "Enemy/Components/EnemyStateComponent.h"

FString UEnemySetWaitMode::GetNotifyName_Implementation() const
{
	return "SetWaitMode";
}

void UEnemySetWaitMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UEnemyStateComponent* state = MeshComp->GetOwner()->FindComponentByClass<UEnemyStateComponent>();

	if (!state) return;

	state->SetWaitMode();
}

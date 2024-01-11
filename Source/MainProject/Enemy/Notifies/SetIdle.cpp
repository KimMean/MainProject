#include "Enemy/Notifies/SetIdle.h"

#include "Enemy/Components/EnemyStateComponent.h"

FString USetIdle::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void USetIdle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UEnemyStateComponent* state = MeshComp->GetOwner()->FindComponentByClass<UEnemyStateComponent>();

	if (!state) return;

	state->SetIdleMode();
}

#include "Enemy/Notifies/EndEnemyAttack.h"

#include "Enemy/Components/EnemyStateComponent.h"

FString UEndEnemyAttack::GetNotifyName_Implementation() const
{
	return "EndAttack";
}

void UEndEnemyAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UEnemyStateComponent* status = MeshComp->GetOwner()->FindComponentByClass<UEnemyStateComponent>();

	if (!status) return;

	status->SetIdleMode();
}

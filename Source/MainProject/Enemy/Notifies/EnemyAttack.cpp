#include "Enemy/Notifies/EnemyAttack.h"

#include "Enemy/EnemyBase.h"

FString UEnemyAttack::GetNotifyName_Implementation() const
{
	return "Attack";
}

void UEnemyAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp->GetWorld()->WorldType == EWorldType::EditorPreview) return;

	Cast<AEnemyBase>(MeshComp->GetOwner())->Attack();
}

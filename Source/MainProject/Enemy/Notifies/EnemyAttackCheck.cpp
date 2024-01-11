#include "Enemy/Notifies/EnemyAttackCheck.h"

#include "Enemy/Charger/Charger.h"

FString UEnemyAttackCheck::GetNotifyName_Implementation() const
{
	return "AttackCheck";
}

void UEnemyAttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp->GetWorld()->WorldType == EWorldType::Type::EditorPreview)
		return;

	Cast<ACharger>(MeshComp->GetOwner())->SetCollisionActive(true);
}

void UEnemyAttackCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp->GetWorld()->WorldType == EWorldType::Type::EditorPreview)
		return;

	Cast<ACharger>(MeshComp->GetOwner())->SetCollisionActive(false);
}

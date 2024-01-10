#include "Enemy/Notifies/EnemyDeath.h"

#include "Enemy/EnemyBase.h"

#include "Utilities/DebugLog.h"
FString UEnemyDeath::GetNotifyName_Implementation() const
{
	return "Death";
}

void UEnemyDeath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{	
	if (MeshComp->GetWorld()->WorldType == EWorldType::Type::EditorPreview)
		return;

	AEnemyBase* enemy = Cast<AEnemyBase>(MeshComp->GetOwner());

	enemy->Death();
}

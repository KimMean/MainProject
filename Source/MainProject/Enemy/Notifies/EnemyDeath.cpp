#include "Enemy/Notifies/EnemyDeath.h"

#include "Enemy/Corpse/Corpse.h"

#include "Utilities/DebugLog.h"
FString UEnemyDeath::GetNotifyName_Implementation() const
{
	return "Death";
}

void UEnemyDeath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{	
	if (MeshComp->GetWorld()->WorldType == EWorldType::Type::EditorPreview)
		return;

	ACorpse* enemy = Cast<ACorpse>(MeshComp->GetOwner());

	enemy->Death();
}

#include "Character/Notifies/AN_GhostTrail.h"

#include "Character/Character_TwinBlast.h"

FString UAN_GhostTrail::GetNotifyName_Implementation() const
{
	return "GhostTrail";
}

void UAN_GhostTrail::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp->GetWorld()->WorldType == EWorldType::EditorPreview) return;

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());
	if (!character) return;
	character->OnCopyPose();
}

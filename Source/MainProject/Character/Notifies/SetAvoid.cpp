#include "Character/Notifies/SetAvoid.h"

#include "Character/Character_TwinBlast.h"

FString USetAvoid::GetNotifyName_Implementation() const
{
	return "SetAvoid";
}

void USetAvoid::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp->GetWorld()->WorldType == EWorldType::EditorPreview) return;

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());
	if (!character) return;

	if(bIsAvoid)
		character->Begin_Roll();
	else
		character->End_Roll();
}

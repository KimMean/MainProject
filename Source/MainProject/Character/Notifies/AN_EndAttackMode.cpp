#include "Character/Notifies/AN_EndAttackMode.h"

#include "Character/Character_TwinBlast.h"

void UAN_EndAttackMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->EndAttackMode();
}

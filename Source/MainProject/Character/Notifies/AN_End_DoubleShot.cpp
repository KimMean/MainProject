#include "Character/Notifies/AN_End_DoubleShot.h"
#include "Character/Character_TwinBlast.h"

void UAN_End_DoubleShot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->End_DoubleShot();
}

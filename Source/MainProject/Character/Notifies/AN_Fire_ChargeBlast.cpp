#include "Character/Notifies/AN_Fire_ChargeBlast.h"

#include "Character/Character_TwinBlast.h"

void UAN_Fire_ChargeBlast::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->Firing(MeshComp->GetSocketByName("Fire_ChargeBlast"));
}

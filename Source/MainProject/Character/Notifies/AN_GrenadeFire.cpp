#include "Character/Notifies/AN_GrenadeFire.h"

#include "Character/Character_TwinBlast.h"

void UAN_GrenadeFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->Firing(MeshComp->GetSocketByName("Muzzle_Grenade"));
}

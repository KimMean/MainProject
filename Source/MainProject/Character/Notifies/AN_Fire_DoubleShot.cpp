#include "Character/Notifies/AN_Fire_DoubleShot.h"
#include "Character/Character_TwinBlast.h"

FString UAN_Fire_DoubleShot::GetNotifyName_Implementation() const
{
	return "Bullet Fire";
}

void UAN_Fire_DoubleShot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;
	
	//character->BulletFiring(MeshComp->GetSocketByName("Muzzle_01"));
	character->Firing(MeshComp->GetSocketByName(SocketName));

}

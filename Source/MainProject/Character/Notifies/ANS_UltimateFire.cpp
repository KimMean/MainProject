#include "Character/Notifies/ANS_UltimateFire.h"

#include "Character/Character_TwinBlast.h"
#include "Utilities/DebugLog.h"

void UANS_UltimateFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ElapsedTime = 0.0f;
}

void UANS_UltimateFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACharacter_TwinBlast* character = Cast<ACharacter_TwinBlast>(MeshComp->GetOwner());

	if (character == nullptr) return;

	ElapsedTime += FrameDeltaTime;
	if (ElapsedTime >= FireDelay)
	{
		ElapsedTime -= FireDelay;
		character->BulletFiring(MeshComp->GetSocketByName("Muzzle_01"));
		character->BulletFiring(MeshComp->GetSocketByName("Muzzle_02"));
	}

}

void UANS_UltimateFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

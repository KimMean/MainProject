#include "Character/Notifies/ANS_DoubleShot.h"
#include "Character/Components/StatusComponent.h"


FString UANS_DoubleShot::GetNotifyName_Implementation() const
{
	return "DoubleShot";
}

void UANS_DoubleShot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	UStatusComponent* Status = MeshComp->GetOwner()->FindComponentByClass<UStatusComponent>();

	if (Status == nullptr) return;

	Status->SetEnableCombo(true);
}

void UANS_DoubleShot::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	UStatusComponent* Status = MeshComp->GetOwner()->FindComponentByClass<UStatusComponent>();

	if (Status == nullptr) return;

	Status->SetEnableCombo(false);
}

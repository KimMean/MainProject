#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_DoubleShot.generated.h"

UCLASS()
class MAINPROJECT_API UANS_DoubleShot : public UAnimNotifyState
{
	GENERATED_BODY()

public :
	FString GetNotifyName_Implementation() const override;

public :
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};

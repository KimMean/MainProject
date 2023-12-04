#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_EndAttackMode.generated.h"

UCLASS()
class MAINPROJECT_API UAN_EndAttackMode : public UAnimNotify
{
	GENERATED_BODY()

public :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

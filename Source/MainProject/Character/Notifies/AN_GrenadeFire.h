#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_GrenadeFire.generated.h"

UCLASS()
class MAINPROJECT_API UAN_GrenadeFire : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

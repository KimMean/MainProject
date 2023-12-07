#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_Fire_ChargeBlast.generated.h"

UCLASS()
class MAINPROJECT_API UAN_Fire_ChargeBlast : public UAnimNotify
{
	GENERATED_BODY()
	

public :
	UFUNCTION()
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

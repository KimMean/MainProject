#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SetAvoid.generated.h"

UCLASS()
class MAINPROJECT_API USetAvoid : public UAnimNotify
{
	GENERATED_BODY()

public :
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private :
	UPROPERTY(EditAnywhere)
		bool bIsAvoid;
};

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyDeath.generated.h"

UCLASS()
class MAINPROJECT_API UEnemyDeath : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	FString GetNotifyName_Implementation() const override;

public :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

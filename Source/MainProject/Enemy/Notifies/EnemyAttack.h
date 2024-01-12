#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyAttack.generated.h"

UCLASS()
class MAINPROJECT_API UEnemyAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

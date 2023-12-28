#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyNameTag.generated.h"

class UTextBlock;

UCLASS()
class MAINPROJECT_API UEnemyNameTag : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void SetNameTag(FText InName);

protected :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* NameTag;
};

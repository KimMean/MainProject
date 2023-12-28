#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHelthPoint.generated.h"

class UProgressBar;

UCLASS()
class MAINPROJECT_API UEnemyHelthPoint : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void Set_HelthPoint_Percent(float InPercent);
	void Set_HelthPoint_Percent(float InCurValue, float InMaxValue);

protected :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HP_Bar;
};

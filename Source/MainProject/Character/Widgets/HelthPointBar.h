#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelthPointBar.generated.h"

UCLASS()
class MAINPROJECT_API UHelthPointBar : public UUserWidget
{
	GENERATED_BODY()


public :
	void Set_PB_HPBar_Percent(float InPercent);

protected :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* PB_HPBar;


	
};

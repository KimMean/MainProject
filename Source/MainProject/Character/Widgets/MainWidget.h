#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class MAINPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void Set_WBP_HPBar_Percent(float InPercent);


protected :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHelthPointBar * WBP_HelthPointBar;
};

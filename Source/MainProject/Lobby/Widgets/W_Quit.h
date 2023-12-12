#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Quit.generated.h"

UCLASS()
class MAINPROJECT_API UW_Quit : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void Btn_Quit_OnClick();

public :
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Cancel;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Quit;
};

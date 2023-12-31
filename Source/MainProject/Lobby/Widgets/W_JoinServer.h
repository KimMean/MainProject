#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_JoinServer.generated.h"

UCLASS()
class MAINPROJECT_API UW_JoinServer : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void Btn_Connect_OnClick();

public :
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Cancel;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Connect;
};

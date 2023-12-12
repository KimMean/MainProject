#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_HostServer.generated.h"

UCLASS()
class MAINPROJECT_API UW_HostServer : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void Btn_Create_OnClick();

public :
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Cancel;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Create;
};

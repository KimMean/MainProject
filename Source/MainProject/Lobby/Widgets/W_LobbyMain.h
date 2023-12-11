#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LobbyMain.generated.h"

UCLASS()
class MAINPROJECT_API UW_LobbyMain : public UUserWidget
{
	GENERATED_BODY()
	
	enum class LobbyMenu : uint8
	{
		NONE,
		Online,
		Host,
		Join,
		Option,
		Quit,
	};

private :
	virtual void NativeConstruct() override;

public :
	UFUNCTION()
		void OnlineServerButtonOnClick();
	UFUNCTION()
		void HostServerButtonOnClick();
	UFUNCTION()
		void JoinServerButtonOnClick();
	UFUNCTION()
		void OptionButtonOnClick();
	UFUNCTION()
		void QuitButtonOnClick();

public :
	void HideMenuWidget();


private :
	void MenuWidgetSwitch(LobbyMenu InMenuIndex);

private :
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_OnlineServer;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_HostServer;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_JoinServer;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Option;
	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_Quit;
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* WS_WidgetSwitcher;
};

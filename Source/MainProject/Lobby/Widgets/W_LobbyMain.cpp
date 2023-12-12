#include "Lobby/Widgets/W_LobbyMain.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "Lobby/Widgets/W_OnlineServer.h"
#include "Lobby/Widgets/W_HostServer.h"
#include "Lobby/Widgets/W_JoinServer.h"
#include "Lobby/Widgets/W_OptionSetting.h"
#include "Lobby/Widgets/W_Quit.h"
#include "Utilities/DebugLog.h"

void UW_LobbyMain::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_OnlineServer->OnClicked.AddDynamic(this, &UW_LobbyMain::OnlineServerButtonOnClick);
	Btn_HostServer->OnClicked.AddDynamic(this, &UW_LobbyMain::HostServerButtonOnClick);
	Btn_JoinServer->OnClicked.AddDynamic(this, &UW_LobbyMain::JoinServerButtonOnClick);
	Btn_Option->OnClicked.AddDynamic(this, &UW_LobbyMain::OptionButtonOnClick);
	Btn_Quit->OnClicked.AddDynamic(this, &UW_LobbyMain::QuitButtonOnClick);

	WBP_OnlineServer->Btn_Cancel->OnClicked.AddDynamic(this, &UW_LobbyMain::CancelButtonOnClick);
	WBP_HostServer->Btn_Cancel->OnClicked.AddDynamic(this, &UW_LobbyMain::CancelButtonOnClick);
	WBP_JoinServer->Btn_Cancel->OnClicked.AddDynamic(this, &UW_LobbyMain::CancelButtonOnClick);
	//WBP_Option->Btn_Cancel->OnClicked.AddDynamic(this, &UW_LobbyMain::CancelButtonOnClick);
	WBP_Quit->Btn_Cancel->OnClicked.AddDynamic(this, &UW_LobbyMain::CancelButtonOnClick);
}

void UW_LobbyMain::OnlineServerButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::Online);
}

void UW_LobbyMain::HostServerButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::Host);
}

void UW_LobbyMain::JoinServerButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::Join);
}

void UW_LobbyMain::OptionButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::Option);
}

void UW_LobbyMain::QuitButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::Quit);
}

void UW_LobbyMain::CancelButtonOnClick()
{
	MenuWidgetSwitch(LobbyMenu::NONE);
}

void UW_LobbyMain::MenuWidgetSwitch(LobbyMenu InMenuIndex)
{
	WS_WidgetSwitcher->SetActiveWidgetIndex((int32)InMenuIndex);
}

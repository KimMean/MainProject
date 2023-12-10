#include "Lobby/LSA_LobbyLevel.h"
#include "Lobby/Widgets/W_LobbyMain.h"

ALSA_LobbyLevel::ALSA_LobbyLevel()
{
	ConstructorHelpers::FClassFinder<UW_LobbyMain> widget(L"WidgetBlueprint'/Game/Lobby/Widgets/WBP_LobbyMain.WBP_LobbyMain_C'");
	LobbyWidgetClass = widget.Class;

}

void ALSA_LobbyLevel::BeginPlay()
{
	LobbyWidget = CreateWidget<UW_LobbyMain>(GetWorld(), LobbyWidgetClass);
	LobbyWidget->AddToViewport();
	
}

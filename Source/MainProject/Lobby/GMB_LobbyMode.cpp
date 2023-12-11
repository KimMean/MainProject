#include "Lobby/GMB_LobbyMode.h"

AGMB_LobbyMode::AGMB_LobbyMode()
{
	GameSessionClass = nullptr;
	//DefaultPawnClass = nullptr;
	HUDClass = nullptr;
	//PlayerControllerClass = nullptr;
	GameStateClass = nullptr;
	PlayerStateClass = nullptr;
	SpectatorClass = nullptr;
	ReplaySpectatorPlayerControllerClass = nullptr;
	ServerStatReplicatorClass = nullptr;

	ConstructorHelpers::FClassFinder<APawn> player(L"Blueprint'/Game/Lobby/BP_LobbyPlayer.BP_LobbyPlayer_C'");
	DefaultPawnClass = player.Class;
	
	
}

#include "Lobby/LSA_LobbyLevel.h"
#include "Lobby/Widgets/W_LobbyMain.h"

ALSA_LobbyLevel::ALSA_LobbyLevel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UW_LobbyMain> widget(L"WidgetBlueprint'/Game/Lobby/Widgets/WBP_LobbyMain.WBP_LobbyMain_C'");
	LobbyWidgetClass = widget.Class;

	FDebug::DumpStackTraceToLog(ELogVerbosity::Verbose);
}

void ALSA_LobbyLevel::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	FDebug::DumpStackTraceToLog(ELogVerbosity::Verbose);
}

void ALSA_LobbyLevel::BeginPlay()
{
	LobbyWidget = CreateWidget<UW_LobbyMain>(GetWorld(), LobbyWidgetClass);
	LobbyWidget->AddToViewport();

	FDebug::DumpStackTraceToLog(ELogVerbosity::Verbose);
}

#include "MainProjectGameModeBase.h"

#include "MainHUD.h"
#include "Character/DefaultCharacter.h"

AMainProjectGameModeBase::AMainProjectGameModeBase()
{
	ConstructorHelpers::FClassFinder<AMainHUD> hud(L"Blueprint'/Game/Settings/BP_MainHUD.BP_MainHUD_C'");
	verifyf(hud.Succeeded(), L"class.Succeeded!");


	HUDClass = hud.Class;
}

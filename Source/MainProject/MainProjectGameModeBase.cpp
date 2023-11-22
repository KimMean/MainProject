#include "MainProjectGameModeBase.h"

#include "MainHUD.h"
#include "Character/Character_TwinBlast.h"

AMainProjectGameModeBase::AMainProjectGameModeBase()
{
	ConstructorHelpers::FClassFinder<AMainHUD> hud(L"Blueprint'/Game/Settings/BP_MainHUD.BP_MainHUD_C'");
	verifyf(hud.Succeeded(), L"class.Succeeded!");

	ConstructorHelpers::FClassFinder<APawn> pawn(L"Blueprint'/Game/Characters/TwinBlast/BP_Character_TwinBlast.BP_Character_TwinBlast_C'");

	HUDClass = hud.Class;
	DefaultPawnClass = pawn.Class;
}

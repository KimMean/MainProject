#include "Lobby/Widgets/W_Quit.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Components/Button.h"

void UW_Quit::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Quit->OnClicked.AddDynamic(this, &UW_Quit::Btn_Quit_OnClick);
}

void UW_Quit::Btn_Quit_OnClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}


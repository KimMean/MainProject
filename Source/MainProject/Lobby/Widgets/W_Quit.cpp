#include "Lobby/Widgets/W_Quit.h"

#include "Components/Button.h"

void UW_Quit::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Quit->OnClicked.AddDynamic(this, &UW_Quit::Btn_Quit_OnClick);
}

void UW_Quit::Btn_Quit_OnClick()
{
}


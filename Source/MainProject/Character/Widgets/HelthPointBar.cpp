#include "Character/Widgets/HelthPointBar.h"

#include "Components/ProgressBar.h"

void UHelthPointBar::Set_PB_HPBar_Percent(float InPercent)
{
	PB_HPBar->SetPercent(InPercent);
}

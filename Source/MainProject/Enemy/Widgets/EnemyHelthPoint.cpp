#include "Enemy/Widgets/EnemyHelthPoint.h"

#include "Components/ProgressBar.h"

void UEnemyHelthPoint::Set_HelthPoint_Percent(float InPercent)
{
	HP_Bar->SetPercent(InPercent);
}

void UEnemyHelthPoint::Set_HelthPoint_Percent(float InCurValue, float InMaxValue)
{
	HP_Bar->SetPercent(InCurValue / InMaxValue);
}

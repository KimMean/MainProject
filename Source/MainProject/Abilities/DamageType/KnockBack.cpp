#include "Abilities/DamageType/KnockBack.h"

#include "Utilities/DebugLog.h"

UKnockBack::UKnockBack()
{
	SetDamageType(FDamageType::KnockBack);
	KnockBackPower = 1000;
}

float UKnockBack::GetKnockBackPower()
{
	return KnockBackPower;
}

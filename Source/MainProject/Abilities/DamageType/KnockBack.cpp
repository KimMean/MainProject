#include "Abilities/DamageType/KnockBack.h"

#include "Utilities/DebugLog.h"

UKnockBack::UKnockBack()
{
	SetDamageType(FDamageType::KnockBack);
	KnockBackPower = 10;
}

float UKnockBack::GetKnockBackPower()
{
	DebugLog::Print("KnockBack");
	DebugLog::Print(KnockBackPower);
	return KnockBackPower;
}

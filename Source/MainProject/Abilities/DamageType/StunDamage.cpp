#include "Abilities/DamageType/StunDamage.h"

UStunDamage::UStunDamage()
{
	SetDamageType(FDamageType::Stun);
	StunTime = 2.0f;
}

float UStunDamage::GetStunTime()
{
	return StunTime;
}

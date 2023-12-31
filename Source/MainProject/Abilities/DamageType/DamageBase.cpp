#include "Abilities/DamageType/DamageBase.h"

#include "Utilities/DebugLog.h"

void UDamageBase::SetDamageType(FDamageType InDamageType)
{
    DamageType = InDamageType;
}

FDamageType UDamageBase::GetDamageType()
{
    return DamageType;
}

float UDamageBase::GetKnockBackPower()
{
    return KnockBackPower;
}

float UDamageBase::GetStunTime()
{
    return StunTime;
}

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DamageType/DamageBase.h"
#include "KnockBack.generated.h"

UCLASS()
class MAINPROJECT_API UKnockBack : public UDamageBase
{
	GENERATED_BODY()
	
private :
	float KnockBackPower;
};

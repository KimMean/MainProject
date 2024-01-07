#pragma once

#include "CoreMinimal.h"
#include "Abilities/DamageType/DamageBase.h"
#include "StunDamage.generated.h"

UCLASS()
class MAINPROJECT_API UStunDamage : public UDamageBase
{
	GENERATED_BODY()
	
public :
	UStunDamage();

public :
	virtual float GetStunTime() override;
};

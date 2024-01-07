#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageBase.generated.h"

UENUM(BlueprintType)
enum class FDamageType : uint8
{
	None,
	KnockBack,
	Stun,
	Max,
};


UCLASS()
class MAINPROJECT_API UDamageBase : public UDamageType
{
	GENERATED_BODY()
	
public :
	void SetDamageType(FDamageType InDamageType);
	FDamageType GetDamageType();

public :
	virtual float GetKnockBackPower();
	virtual float GetStunTime();

protected :
	float KnockBackPower = 0;
	float StunTime = 0;

private :
	FDamageType DamageType;
};

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Grenadier.generated.h"

class ABomb;

UCLASS()
class MAINPROJECT_API AGrenadier : public AEnemyBase
{
	GENERATED_BODY()

public:
	AGrenadier();

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Attack() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<ABomb> Bomb;
};

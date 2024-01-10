#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Wizard.generated.h"

UCLASS()
class MAINPROJECT_API AWizard : public AEnemyBase
{
	GENERATED_BODY()

public:
	AWizard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};

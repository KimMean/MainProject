#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Sploder.generated.h"

class UParticleSystem;

UCLASS()
class MAINPROJECT_API ASploder : public AEnemyBase
{
	GENERATED_BODY()

public:
	ASploder();

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public :
	void BombTimeCountDown();

private :
	UPROPERTY(VisibleDefaultsOnly)
		UParticleSystem* ImpactParticle;

	FTimerHandle BombTimer;
	int32 BombTime = 5;
};

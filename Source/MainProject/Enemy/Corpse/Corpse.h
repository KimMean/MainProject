#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Corpse.generated.h"

class AEnemy_Sword;

UCLASS()
class MAINPROJECT_API ACorpse : public AEnemyBase
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public :
	virtual void Death() override;

public :
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void EquipmentSword();

private :
	UPROPERTY(VisibleDefaultsOnly)
		AEnemy_Sword* Sword;
};

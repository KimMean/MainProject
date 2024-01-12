#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Charger.generated.h"

class USphereComponent;

UCLASS()
class MAINPROJECT_API ACharger : public AEnemyBase
{
	GENERATED_BODY()

public:
	ACharger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public :
	void SetCollisionActive(bool InActive);

private :
	void InitDelegates();

private :
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private :
	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereCollider;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class MAINPROJECT_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AFireBall();

protected:
	virtual void BeginPlay() override;

public :
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetDirection(FVector InDirection);

private :
	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereCollider;

	UPROPERTY(VisibleDefaultsOnly)
		UParticleSystemComponent* ParticleSystem;

private :
	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileMovement;
};

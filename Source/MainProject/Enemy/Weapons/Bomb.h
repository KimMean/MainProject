#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class MAINPROJECT_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	ABomb();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetDirection(const FVector& InDirection);

private :

	UPROPERTY(VisibleDefaultsOnly)
		USphereComponent* SphereCollider;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly, Category = "ImpactParticle")
		UParticleSystem* ImpactParticle;
};

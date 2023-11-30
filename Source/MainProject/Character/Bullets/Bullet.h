#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class MAINPROJECT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	void SetDirection(FVector InDirection);

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		class UProjectileMovementComponent* ProjectileMovement;

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class MAINPROJECT_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrenade();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	void SetProjectileDirection(const FVector& InDirection);

public :
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private :
	UPROPERTY(VisibleDefaultsOnly, Category = "ImpactParticle")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Decal")
		class UMaterialInstanceConstant* DecalMaterial;

	UPROPERTY(EditAnywhere)
		FVector DecalSize;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;



};

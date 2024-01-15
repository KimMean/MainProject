#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChargeBolt.generated.h"

UCLASS()
class MAINPROJECT_API AChargeBolt : public AActor
{
	GENERATED_BODY()
	
public:	
	AChargeBolt();

protected:
	virtual void BeginPlay() override;

public:
	void SetDirection(FVector InDirection);

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private :
	UPROPERTY(VisibleDefaultsOnly, Category = "Material")
		class UMaterial* Material;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* ImpactParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Decal")
		class UMaterialInstanceConstant* DecalMaterial;

	UPROPERTY(EditAnywhere)
		FVector DecalSize;

	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<UDamageType> DamageType;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class USoundBase* Sound;
};

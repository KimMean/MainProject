#include "Character/Bullets/ChargeBolt.h"

#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Abilities/DamageType/KnockBack.h"

#include "Utilities/DebugLog.h"

AChargeBolt::AChargeBolt()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = SphereCollision;
	StaticMesh->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(50.0f);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/BasicShape/Sphere.Sphere'");
	StaticMesh->SetWorldScale3D(FVector(1.0f));
	StaticMesh->SetStaticMesh(mesh.Object);

	Projectile->SetUpdatedComponent(SphereCollision);
	Projectile->InitialSpeed = 3e+3f;
	Projectile->MaxSpeed = 3e+3f;
	Projectile->ProjectileGravityScale = 0.0f;

	ConstructorHelpers::FObjectFinder<UMaterial> material(L"Material'/Game/Characters/Bullets/M_ChargeBolt.M_ChargeBolt'");
	Material = material.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_GrenadeRadial.P_GrenadeRadial'");
	ImpactParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Characters/Bullets/BulletDecal/M_Decal_Inst.M_Decal_Inst'");
	DecalMaterial = decal.Object;
	ConstructorHelpers::FClassFinder<UKnockBack> damageType(L"Class'/Script/MainProject.KnockBack'");
	DamageType = damageType.Class;
}

void AChargeBolt::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AChargeBolt::OnBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AChargeBolt::OnEndOverlap);

	StaticMesh->SetMaterial(0, Material);
}

void AChargeBolt::SetDirection(FVector InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
}

void AChargeBolt::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (!Cast<ACharacter>(OtherActor)) return;

	FRotator rotator = SweepResult.ImpactNormal.Rotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, SweepResult.Location, rotator);
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecalSize, SweepResult.Location, rotator, 10.0f);

	UGameplayStatics::ApplyDamage(OtherActor, 10, GetOwner()->GetInstigatorController(), this, DamageType);

	Destroy();
}

void AChargeBolt::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



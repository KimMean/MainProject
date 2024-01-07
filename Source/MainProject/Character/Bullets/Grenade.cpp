#include "Character/Bullets/Grenade.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"

#include "Abilities/DamageType/StunDamage.h"

#include "Utilities/DebugLog.h"

AGrenade::AGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = BoxCollision;
	StaticMesh->SetupAttachment(RootComponent);
	
	BoxCollision->SetBoxExtent(FVector(50.0f, 30.0f, 30.0f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/BasicShape/Cylinder.Cylinder'");
	StaticMesh->SetStaticMesh(mesh.Object);
	StaticMesh->SetRelativeScale3D(FVector(0.4f, 0.6f, 1.0f));
	StaticMesh->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Projectile->SetUpdatedComponent(BoxCollision);
	Projectile->InitialSpeed = 3e+3f;
	Projectile->MaxSpeed = 3e+3f;

	ConstructorHelpers::FObjectFinder<UMaterial> material(L"Material'/Game/Characters/Bullets/M_Grenade.M_Grenade'");
	Material = material.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_TwinBlast_VortexGrenade_ExplodeBallistic.P_TwinBlast_VortexGrenade_ExplodeBallistic'");
	ImpactParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Characters/Bullets/BulletDecal/M_Decal_Inst.M_Decal_Inst'");
	DecalMaterial = decal.Object;

	ConstructorHelpers::FClassFinder<UStunDamage> damageType(L"Class'/Script/MainProject.StunDamage'");
	DamageType = damageType.Class;
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrenade::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AGrenade::OnEndOverlap);

	StaticMesh->SetMaterial(0, Material);
}

void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::SetProjectileDirection(const FVector& InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
}

void AGrenade::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	FRotator rotator = SweepResult.ImpactNormal.Rotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, SweepResult.Location, rotator);
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecalSize, SweepResult.Location, rotator, 10.0f);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);
	ignoreActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 20, GetActorLocation(), 300.0f, DamageType, ignoreActors, this, GetOwner()->GetInstigatorController(), false);

	Destroy();
}

void AGrenade::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


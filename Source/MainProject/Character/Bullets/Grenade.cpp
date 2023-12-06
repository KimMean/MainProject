#include "Character/Bullets/Grenade.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"

#include "Utilities/DebugLog.h"

AGrenade::AGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = BoxCollision;
	StaticMesh->SetupAttachment(RootComponent);
	
	BoxCollision->SetWorldScale3D(FVector(0.5f, 0.3f, 0.3f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/BasicShape/Cylinder.Cylinder'");
	StaticMesh->SetStaticMesh(mesh.Object);
	StaticMesh->SetRelativeScale3D(FVector(0.4f, 0.6f, 1.0f));
	StaticMesh->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Projectile->SetUpdatedComponent(BoxCollision);
	Projectile->InitialSpeed = 3e+3f;
	Projectile->MaxSpeed = 3e+3f;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_GrenadeRadial.P_GrenadeRadial'");
	ImpactParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Characters/Bullets/BulletDecal/M_Decal_Inst.M_Decal_Inst'");
	DecalMaterial = decal.Object;
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrenade::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AGrenade::OnEndOverlap);
	
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
	DebugLog::Print(SweepResult.GetActor()->GetName());
	FRotator rotator = SweepResult.ImpactNormal.Rotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, SweepResult.Location, rotator);
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecalSize, SweepResult.Location, rotator, 10.0f);
	Destroy();
}

void AGrenade::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


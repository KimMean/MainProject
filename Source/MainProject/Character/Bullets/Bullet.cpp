#include "Character/Bullets/Bullet.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceConstant.h"

#include "Utilities/DebugLog.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//ParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("ParticleSystem"));

	RootComponent = SphereCollision;
	StaticMesh->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(5.0f);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/BasicShape/Sphere.Sphere'");
	StaticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	StaticMesh->SetStaticMesh(mesh.Object);

	ProjectileMovement->SetUpdatedComponent(SphereCollision);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ConstructorHelpers::FObjectFinder<UMaterial> material(L"Material'/Game/Characters/Bullets/M_Bullet_Material.M_Bullet_Material'");
	Material = material.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/Nitro/FX/P_TwinBlast_Nitro_NoHit.P_TwinBlast_Nitro_NoHit'");
	ImpactParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> decal(L"MaterialInstanceConstant'/Game/Characters/Bullets/BulletDecal/M_Decal_Inst.M_Decal_Inst'");
	DecalMaterial = decal.Object;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnEndOverlap);

	StaticMesh->SetMaterial(0, Material);

}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::SetDirection(FVector InDirection)
{
	ProjectileMovement->Velocity = InDirection * ProjectileMovement->InitialSpeed;
}

void ABullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//DebugLog::Print(OtherActor->GetFName().ToString());

	FRotator rotator = SweepResult.ImpactNormal.Rotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, SweepResult.Location, rotator);
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecalSize, SweepResult.Location, rotator, 10.0f);
	Destroy();
	//SweepResult.ImpactNormal
}

void ABullet::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//DebugLog::Print(OtherActor->GetFName().ToString());
}

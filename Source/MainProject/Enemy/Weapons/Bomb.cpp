#include "Enemy/Weapons/Bomb.h"

#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"

ABomb::ABomb()
{
	Tags.Add("Enemy");

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = SphereCollider;
	StaticMesh->SetupAttachment(RootComponent);

	SphereCollider->InitSphereRadius(15);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/BasicShape/Sphere.Sphere'");
	StaticMesh->SetStaticMesh(mesh.Object);
	StaticMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	Projectile->SetUpdatedComponent(RootComponent);
	Projectile->InitialSpeed = 3e+3f;
	Projectile->MaxSpeed = 3e+3f;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_explosion.P_ky_explosion'");
	ImpactParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> sound(L"SoundWave'/Game/Characters/Sound/explosion.explosion'");
	Sound = sound.Object;
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBeginOverlap);
}

void ABomb::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorTransform());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);
	ignoreActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 20, GetActorLocation(), 300.0f, UDamageType::StaticClass(), ignoreActors, this, GetOwner()->GetInstigatorController(), false);

	Destroy();
}

void ABomb::SetDirection(const FVector& InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
}


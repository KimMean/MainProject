#include "Enemy/Weapons/FireBall.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

AFireBall::AFireBall()
{
	Tags.Add("Enemy");

	//SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	SetRootComponent(SphereCollider);
	ParticleSystem->SetupAttachment(RootComponent);

	SphereCollider->InitSphereRadius(50);

	// Projectile ����
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'");
	ParticleSystem->SetTemplate(particle.Object);

	ConstructorHelpers::FObjectFinder<UParticleSystem> impact(L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_hit2.P_ky_hit2'");
	ImpactParticle = impact.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> sound(L"SoundWave'/Game/Characters/Sound/smallExplosion.smallExplosion'");
	Sound = sound.Object;
}

void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnComponentBeginOverlap);
}

void AFireBall::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Enemy")) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorTransform());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 0.5f);

	UGameplayStatics::ApplyDamage(OtherActor, 10, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}

void AFireBall::SetDirection(FVector InDirection)
{
	ProjectileMovement->Velocity = InDirection * ProjectileMovement->InitialSpeed;
}


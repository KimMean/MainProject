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

	// Projectile ¼³Á¤
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'");
	ParticleSystem->SetTemplate(particle.Object);
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

	UGameplayStatics::ApplyDamage(OtherActor, 10, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}

void AFireBall::SetDirection(FVector InDirection)
{
	ProjectileMovement->Velocity = InDirection * ProjectileMovement->InitialSpeed;
}


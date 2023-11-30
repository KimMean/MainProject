#include "Character/Bullets/Bullet.h"

#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->InitSphereRadius(5.0f);
	RootComponent = SphereCollision;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	StaticMesh->SetStaticMesh(mesh.Object);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(SphereCollision);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;


}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::SetDirection(FVector InDirection)
{
	ProjectileMovement->Velocity = InDirection * ProjectileMovement->InitialSpeed;
}


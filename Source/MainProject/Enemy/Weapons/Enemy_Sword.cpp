#include "Enemy/Weapons/Enemy_Sword.h"

#include "Kismet/GameplayStatics.h"
#include "Gameframework/Character.h"

#include "Components/BoxComponent.h"

#include "Utilities/DebugLog.h"

AEnemy_Sword::AEnemy_Sword()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	
	SkeletalMesh->SetupAttachment(RootComponent);
	BoxCollision->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game///CityofBrass_Enemies/Meshes/Enemy/Sword/enemy_Sword_Mesh.enemy_Sword_Mesh'");
	SkeletalMesh->SetSkeletalMesh(mesh.Object);

	BoxCollision->SetBoxExtent(FVector(35.0f, 10.0f, 3.0f));
	BoxCollision->SetRelativeLocation(FVector(50.0f, -5.0f, 0.0f));
	
}

void AEnemy_Sword::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Sword::OnComponentBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Sword::OnComponentEndOverlap);
}

void AEnemy_Sword::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	// 공격중일때만 해야함
	UGameplayStatics::ApplyDamage(OtherActor, 5, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
	
}

void AEnemy_Sword::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



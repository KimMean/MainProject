#include "Enemy/Weapons/Enemy_Sword.h"

#include "Components/BoxComponent.h"

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
}



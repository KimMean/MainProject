#include "Enemy/Corpse/Corpse.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Enemy/Weapons/Enemy_Sword.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/Components/EnemyAnimComponent.h"

ACorpse::ACorpse()
{

	State = CreateDefaultSubobject<UEnemyStateComponent>(TEXT("StateComponent"));
	Status = CreateDefaultSubobject<UEnemyStatusComponent>(TEXT("StatusComponent"));
	Animation = CreateDefaultSubobject<UEnemyAnimComponent>(TEXT("AnimationComponent"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();

	AEnemy_Sword* sword = GetWorld()->SpawnActor<AEnemy_Sword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (sword)
	{
		const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName("SwordSocket");
		socket->AttachActor(sword, GetMesh());
	}
}


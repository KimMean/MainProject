#include "Enemy/Grenadier/Grenadier.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/Weapons/Bomb.h"

AGrenadier::AGrenadier()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Grenadier/Grenadier_Mesh.Grenadier_Mesh'");
	GetMesh()->SetSkeletalMesh(mesh.Object);

	AIControllerClass = AEnemy_AIController::StaticClass();

	ConstructorHelpers::FClassFinder<ABomb> bomb(L"Blueprint'/Game/Enemies/Weapons/Bomb/BP_Bomb.BP_Bomb_C'");
	Bomb = bomb.Class;

	NameTag = "Grenadier";
}

void AGrenadier::BeginPlay()
{
	Super::BeginPlay();

	SetNameTag(NameTag);
	UpdateHealthPoint();

	Cast<AEnemy_AIController>(GetController())->SetSenseConfigSight_SightRadius(800);
	Cast<AEnemy_AIController>(GetController())->SetSenseConfigSight_LoseSightRadius(1000);
	Cast<AEnemy_AIController>(GetController())->SetActionRange(600);
}

float AGrenadier::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (State->IsDeathMode())
		return Damage;

	//Cast<AEnemy_AIController>(GetController())->SetTargetPlayer(EventInstigator->GetCharacter());

	UDamageBase* damageType = Cast<UDamageBase>(DamageEvent.DamageTypeClass->GetDefaultObject());
	if (damageType)
	{
		switch (damageType->GetDamageType())
		{
		case FDamageType::KnockBack:
		{
			State->SetHittedMode();
			// 뒤로 밀려나는 애니메이션
			// 넉백
			float power = damageType->GetKnockBackPower();
			LaunchCharacter(-GetActorForwardVector() * power, false, false);
			break;
		}
		case FDamageType::Stun:
			State->SetStunnedMode();
			break;
		}
	}

	return Damage;
}

void AGrenadier::Attack()
{
	if (!Status->GetTarget()) return;

	FVector location = GetMesh()->GetSocketLocation("ThrowSocket");
	FTransform transform(location);
	ABomb* bomb = GetWorld()->SpawnActorDeferred<ABomb>(Bomb, transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (bomb == nullptr) return;

	FVector destination = Status->GetTarget()->GetActorLocation();
	FVector direction = destination - location;

	bomb->SetDirection(direction.GetSafeNormal());
	bomb->FinishSpawning(bomb->GetTransform());
}

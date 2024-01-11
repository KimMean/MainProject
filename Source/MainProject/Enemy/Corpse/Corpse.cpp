#include "Enemy/Corpse/Corpse.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Enemy/Weapons/Enemy_Sword.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"


ACorpse::ACorpse()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse_Basic/Corpse_Basic.Corpse_Basic'");
	GetMesh()->SetSkeletalMesh(mesh.Object);

	AIControllerClass = AEnemy_AIController::StaticClass();
	

}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();

	SetNameTag("Corpse");
	UpdateHealthPoint(); 
	EquipmentSword();
}

void ACorpse::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACorpse::Death()
{
	Sword->Destroy();
	Super::Death();
}

float ACorpse::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (State->IsDeathMode())
		return DamageAmount;

	Cast<AEnemy_AIController>(GetController())->SetTargetPlayer(EventInstigator->GetCharacter());

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
		{
			State->SetStunnedMode();
			float stunTime = damageType->GetStunTime();
			break;
		}
		}
	}

	return DamageAmount;
}


void ACorpse::EquipmentSword()
{
	Sword = GetWorld()->SpawnActor<AEnemy_Sword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (Sword)
	{
		const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName("SwordSocket");
		socket->AttachActor(Sword, GetMesh());
		Sword->SetOwner(this);
	}
}


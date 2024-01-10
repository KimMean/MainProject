#include "Enemy/Wizard/Wizard.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"

AWizard::AWizard()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Wizard/Wizard_Mesh.Wizard_Mesh'");
	GetMesh()->SetSkeletalMesh(mesh.Object);

	AIControllerClass = AEnemy_AIController::StaticClass();
}

void AWizard::BeginPlay()
{
	Super::BeginPlay();

	SetNameTag("Wizard");
	UpdateHealthPoint();
}

void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWizard::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (State->IsDeathMode())
		return Damage;

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
			State->SetStunnedMode();
			break;
		}
	}

	return Damage;
}

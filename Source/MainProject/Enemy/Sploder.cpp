#include "Enemy/Sploder.h"

#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystem.h"

#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"

#include "Utilities/DebugLog.h"

ASploder::ASploder()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Sploder/Sploder_Mesh.Sploder_Mesh'");
	GetMesh()->SetSkeletalMesh(mesh.Object);

	AIControllerClass = AEnemy_AIController::StaticClass();
	Status->SetMaxHealthPoint(50);


	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(L"ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_TwinBlast_VortexGrenade_ExplodeBallistic.P_TwinBlast_VortexGrenade_ExplodeBallistic'");
	ImpactParticle = particle.Object;
}

void ASploder::BeginPlay()
{
	Super::BeginPlay();

	SetNameTag("Sploder");
	UpdateHealthPoint();

	Cast<AEnemy_AIController>(GetController())->SetActionRange(0);
	Cast<AEnemy_AIController>(GetController())->SetSenseConfigSight_SightRadius(0);
	Cast<AEnemy_AIController>(GetController())->SetSenseConfigSight_LoseSightRadius(0);
}

float ASploder::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
			float power = damageType->GetKnockBackPower();
			LaunchCharacter(-GetActorForwardVector() * power, false, false);
			break;
		}
		case FDamageType::Stun:
			State->SetStunnedMode();
			break;
		}
	}

	if (State->IsIdleMode())
		State->SetWaitMode();

	if (!GetWorldTimerManager().IsTimerActive(BombTimer))
		GetWorldTimerManager().SetTimer(BombTimer, this, &ASploder::BombTimeCountDown, 1.0f, true);

	return Damage;
}

void ASploder::BombTimeCountDown()
{
	BombTime--;
	if (BombTime <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetTransform());
		// Æã
		TArray<AActor*> ignore;

		UGameplayStatics::ApplyRadialDamage(GetWorld(), 50, GetActorLocation(), 500.0f, UDamageType::StaticClass(), ignore, this, GetOwner()->GetInstigatorController(), false);
		// Dead
		Status->SetHealthPoint(0);
		UpdateHealthPoint();
		State->SetDeathMode();
		GetWorldTimerManager().ClearTimer(BombTimer);
	}
}

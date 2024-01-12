#include "Enemy/Charger/Charger.h"

#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"

#include "Utilities/DebugLog.h"

ACharger::ACharger()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Charger/Charger.Charger'");
	GetMesh()->SetSkeletalMesh(mesh.Object);

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollider->SetupAttachment(GetMesh());
	SphereCollider->InitSphereRadius(50);
	SphereCollider->AddRelativeLocation(FVector(100, 0, 100));
	

	AIControllerClass = AEnemy_AIController::StaticClass();
}

void ACharger::BeginPlay()
{
	Super::BeginPlay();

	SetNameTag("Charger");
	InitDelegates();
	UpdateHealthPoint();
	SetCollisionActive(false);

	Cast<AEnemy_AIController>(GetController())->SetActionRange(600);
	
}

void ACharger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACharger::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void ACharger::SetCollisionActive(bool InActive)
{
	if (InActive)
	{
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACharger::InitDelegates()
{
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACharger::OnComponentBeginOverlap);
}

void ACharger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy")) return;

	UGameplayStatics::ApplyDamage(OtherActor, 5, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
}


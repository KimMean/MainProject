#include "Enemy/Corpse/Corpse_AI.h"

#include "Enemy/AI/Enemy_AIController.h"
#include "Abilities/DamageType/DamageBase.h"

#include "Utilities/DebugLog.h"

ACorpse_AI::ACorpse_AI()
{
}

void ACorpse_AI::BeginPlay()
{
	Super::BeginPlay();
}

float ACorpse_AI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
			case FDamageType::Stun :
			{
				State->SetStunnedMode();
				float stunTime = damageType->GetStunTime();
				break;
			}
		}
	}


	return DamageAmount;
}

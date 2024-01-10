#include "Enemy/Components/EnemyAnimComponent.h"

#include "Enemy/EnemyBase.h"
#include "Enemy/Datas/EnemyAnimDatas.h"

UEnemyAnimComponent::UEnemyAnimComponent()
{
}


void UEnemyAnimComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UEnemyAnimComponent::Action()
{
	PlayAnimMontage(EEnemyStateType::Action);
}

void UEnemyAnimComponent::Hitted()
{
	PlayAnimMontage(EEnemyStateType::Hitted);
}

void UEnemyAnimComponent::Stunned()
{
	PlayAnimMontage(EEnemyStateType::Stunned);
}

void UEnemyAnimComponent::Death()
{
	PlayAnimMontage(EEnemyStateType::Death);
}


void UEnemyAnimComponent::PlayAnimMontage(EEnemyStateType InState)
{
	AEnemyBase* character = Cast<AEnemyBase>(GetOwner());

	if (!AnimDatas) return;

	const FEnemyAnimData* data = AnimDatas->GetAnimationData(InState);

	if (!data) return;

	character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
}


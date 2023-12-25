#include "Enemy/Components/EnemyAnimComponent.h"

#include "GameFramework/Character.h"
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
	ACharacter* character = Cast<ACharacter>(GetOwner());

	if (!AnimDatas) return;

	const FEnemyAnimData* data = AnimDatas->GetAnimationData(InState);

	if (!data) return;

	character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
	//const FAnimationData* data = Datas[(int32)InState];
	//if (!!data)
	//{
	//	if (!!data->Animation)
	//	{
	//		character->PlayAnimMontage(Cast<UAnimMontage>(data->Animation), data-//>PlayRatio);
	//	}
	//}
}


#include "Character/Components/AnimationComponent.h"

#include "Gameframework/Character.h"
#include "Utilities/DebugLog.h"

UAnimationComponent::UAnimationComponent()
{
}


void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr) return;

	TArray<FAnimationData*> datas;
	DataTable->GetAllRows<FAnimationData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FAnimationData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}
	}

}

void UAnimationComponent::Attack_DoubleShot()
{
	PlayAnimMontage(EStateType::Attack);
}

void UAnimationComponent::Attack_DoubleShotCombo()
{
	PlayAnimMontage(EStateType::DoubleAttack);
}

void UAnimationComponent::Dive_Forward()
{
	PlayAnimMontage(EStateType::Dive_Forward);
}

void UAnimationComponent::Dive_Backward()
{
	PlayAnimation(EStateType::Dive_Backward);
}

void UAnimationComponent::Dive_Right()
{
	PlayAnimation(EStateType::Dive_Right);
}

void UAnimationComponent::Dive_Left()
{
	PlayAnimation(EStateType::Dive_Left);
}


void UAnimationComponent::PlayAnimation(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FAnimationData* data = Datas[(int32)InState];
	if (!!data)
	{
		if (!!data->Animation)
			character->GetMesh()->PlayAnimation(data->Animation, false);
	}
}

void UAnimationComponent::PlayAnimMontage(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	const FAnimationData* data = Datas[(int32)InState];
	if (!!data)
	{
		if (!!data->Animation)
		{
			DebugLog::Print("aaaaaaaaaaa");
			character->PlayAnimMontage(Cast<UAnimMontage>(data->Animation), data->PlayRatio);
		}
	}
}




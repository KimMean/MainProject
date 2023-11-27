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

	//for (const FAnimationData* data : datas)
	//{
	//	if (!!data)
	//		DebugLog::Print(data->Animation->GetPathName());
	//}

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

void UAnimationComponent::Play_Roll()
{
	PlayAnimation(EStateType::Roll);
}

void UAnimationComponent::PlayAnimation(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FAnimationData* data = Datas[(int32)InState];
	if (!!data)
	{
		if (!!data->Animation)
			character->GetMesh()->PlayAnimation(data->Animation, false);
		DebugLog::Log("Rolllllllll");
	}
}




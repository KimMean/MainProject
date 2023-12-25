#include "Enemy/Datas/EnemyAnimDatas.h"

#include "GameFramework/Character.h"

void UEnemyAnimDatas::BeginPlay(ACharacter InOwnerCharacter)
{
}

FEnemyAnimData* UEnemyAnimDatas::GetAnimationData(EEnemyStateType InEnemyStateType)
{
	return &AnimDatas[InEnemyStateType];
}

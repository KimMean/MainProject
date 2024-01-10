#include "Enemy/EnemyAnimInstance.h"

#include "Enemy/EnemyBase.h"

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerEnemy= Cast<AEnemyBase>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerEnemy == nullptr) return;

	Speed = OwnerEnemy->GetVelocity().Size2D();
}


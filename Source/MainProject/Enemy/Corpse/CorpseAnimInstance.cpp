#include "Enemy/Corpse/CorpseAnimInstance.h"

#include "GameFramework/Character.h"

void UCorpseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCorpseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter == nullptr) return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
}

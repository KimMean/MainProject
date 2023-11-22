#include "Character/TwinBlastAnimInstance.h"

#include "GameFramework/Character.h"

void UTwinBlastAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UTwinBlastAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter == nullptr) return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	AimHorizontal = OwnerCharacter->GetBaseAimRotation().Yaw;
	AimVertical = OwnerCharacter->GetBaseAimRotation().Pitch;
}

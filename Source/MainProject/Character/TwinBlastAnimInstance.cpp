#include "Character/TwinBlastAnimInstance.h"

#include "GameFramework/Character.h"
#include "KismetAnimationLibrary.h"

#include "Character_TwinBlast.h"

#include "Utilities/DebugLog.h"

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
	Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	AimHorizontal = 0.0f;
	AimVertical = OwnerCharacter->GetBaseAimRotation().Pitch;


}

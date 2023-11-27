#include "Character/TwinBlastAnimInstance.h"

#include "GameFramework/Character.h"

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
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	//ACharacter_TwinBlast* twinBlast = Cast<ACharacter_TwinBlast>(OwnerCharacter);
	//if (!!twinBlast)
	//{
	//	if (twinBlast->GetAimMode())
	//	{
	//		float rotY = OwnerCharacter->GetViewRotation().Yaw - OwnerCharacter->K2_GetActorRotation().Yaw;
	//		if (rotY > 180)
	//			rotY = rotY - 360;
	//		AimHorizontal = rotY;
	//	}
	//	else
	//	{
	//		AimHorizontal = 0.0f;
	//	}
	//}

	AimHorizontal = 0.0f;
	AimVertical = OwnerCharacter->GetBaseAimRotation().Pitch;

	//OwnerCharacter->GetControlRotation()
	//DebugLog::Print(OwnerCharacter->GetBaseAimRotation(), 1, 1.0f, FColor::Red);
	//DebugLog::Print(OwnerCharacter->GetViewRotation(), 2, 1.0f, FColor::Blue);
	//DebugLog::Print(OwnerCharacter->K2_GetActorRotation(), 3, 1.0f, FColor::Green);

}

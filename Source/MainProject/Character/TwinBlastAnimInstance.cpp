#include "Character/TwinBlastAnimInstance.h"

#include "GameFramework/Character.h"
#include "KismetAnimationLibrary.h"
#include "Net/UnrealNetwork.h"

#include "Character_TwinBlast.h"

#include "Utilities/DebugLog.h"

void UTwinBlastAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	TwinBlast = Cast<ACharacter_TwinBlast>(OwnerCharacter);
	TwinBlast->GetStatus()->OnActionModeChanged.AddDynamic(this, &UTwinBlastAnimInstance::OnActionModeChanged);
}

void UTwinBlastAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter == nullptr) return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	AimHorizontal = 0.0f;
	AimVertical = OwnerCharacter->GetBaseAimRotation().Pitch;

	UInverseKinematicsComponent* IK = TwinBlast->FindComponentByClass<UInverseKinematicsComponent>();
	if (!IK) return;

	IKData = IK->GetIKData();

}

void UTwinBlastAnimInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTwinBlastAnimInstance, Speed);
	DOREPLIFETIME(UTwinBlastAnimInstance, Direction);
	DOREPLIFETIME(UTwinBlastAnimInstance, AimHorizontal);
	DOREPLIFETIME(UTwinBlastAnimInstance, AimVertical);
}

void UTwinBlastAnimInstance::OnActionModeChanged(EActionMode InPrevType, EActionMode InNewType)
{
	ActionMode = InNewType;
}

#include "Enemy/Components/EnemyStatusComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

UEnemyStatusComponent::UEnemyStatusComponent()
{
}


void UEnemyStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyStatusComponent::AdjustHelthPoint(float InAdjustValue)
{
	HelthPoint += InAdjustValue;

	if (HelthPoint <= 0)
		HelthPoint = 0;

	if (HelthPoint > GetMaxHelthPoint())
		HelthPoint = GetMaxHelthPoint();
}

void UEnemyStatusComponent::SetSpeed(EEnemySpeedType InType)
{
	UCharacterMovementComponent* movement = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();

	movement->MaxWalkSpeed = Speed[(int32)InType];
}

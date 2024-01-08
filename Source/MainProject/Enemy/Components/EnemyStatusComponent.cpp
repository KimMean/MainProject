#include "Enemy/Components/EnemyStatusComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

UEnemyStatusComponent::UEnemyStatusComponent()
{
}


void UEnemyStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyStatusComponent::AdjustHealthPoint(float InAdjustValue)
{
	HealthPoint += InAdjustValue;

	if (HealthPoint <= 0)
		HealthPoint = 0;

	if (HealthPoint > GetMaxHealthPoint())
		HealthPoint = GetMaxHealthPoint();
}

void UEnemyStatusComponent::SetSpeed(EEnemySpeedType InType)
{
	UCharacterMovementComponent* movement = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();

	movement->MaxWalkSpeed = Speed[(int32)InType];
}

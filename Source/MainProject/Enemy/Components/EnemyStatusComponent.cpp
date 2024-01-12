#include "Enemy/Components/EnemyStatusComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

UEnemyStatusComponent::UEnemyStatusComponent()
{
}


void UEnemyStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	OnTargetChanged.AddDynamic(this, &UEnemyStatusComponent::OnTargetChange);
}

void UEnemyStatusComponent::AdjustHealthPoint(float InAdjustValue)
{
	HealthPoint += InAdjustValue;

	if (HealthPoint <= 0)
		HealthPoint = 0;

	if (HealthPoint > GetMaxHealthPoint())
		HealthPoint = GetMaxHealthPoint();
}

void UEnemyStatusComponent::SetTarget(ACharacter* InCharacter)
{
	Target = InCharacter;

	if (OnTargetChanged.IsBound())
		OnTargetChanged.Broadcast(Target);
}

ACharacter* UEnemyStatusComponent::GetTarget()
{
	return Target;
}

void UEnemyStatusComponent::SetSpeed(EEnemySpeedType InType)
{
	UCharacterMovementComponent* movement = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();

	movement->MaxWalkSpeed = Speed[(int32)InType];
}

void UEnemyStatusComponent::OnTargetChange(ACharacter* InCharacter)
{
	// TargetChanged
}

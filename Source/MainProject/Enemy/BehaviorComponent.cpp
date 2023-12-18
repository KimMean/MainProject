#include "Enemy/BehaviorComponent.h"

#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"


UBehaviorComponent::UBehaviorComponent()
{

}

void UBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UBehaviorComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UBehaviorComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

bool UBehaviorComponent::IsAvoidMode()
{
	return GetType() == EBehaviorType::Avoid;
}

void UBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

void UBehaviorComponent::SetAvoidMode()
{
	ChangeType(EBehaviorType::Avoid);
}


ACharacter* UBehaviorComponent::GetTargetCharacter()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(PlayerKey));
}

void UBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);	// 블랙보드에 상태 셋팅

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

EBehaviorType UBehaviorComponent::GetType()
{
	return (EBehaviorType)(Blackboard->GetValueAsEnum(BehaviorKey));
}



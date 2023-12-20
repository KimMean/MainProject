#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorComponent.generated.h"

class UBlackboardComponent;
class ACharacter;
class ACharacter_TwinBlast;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, 
	Approach, 
	Action, 
	Patrol, 
	Hitted, 
	Avoid,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPreType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBehaviorComponent();

protected:
	virtual void BeginPlay() override;

private :
	// 블랙보드 키
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";

public :
	UFUNCTION(BlueprintPure)
		bool IsWaitMode();
	UFUNCTION(BlueprintPure)
		bool IsApproachMode();
	UFUNCTION(BlueprintPure)
		bool IsActionMode();
	UFUNCTION(BlueprintPure)
		bool IsPatrolMode();
	UFUNCTION(BlueprintPure)
		bool IsHittedMode();
	UFUNCTION(BlueprintPure)
		bool IsAvoidMode();

	FORCEINLINE void SetBlackboard(UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public :
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();

	ACharacter* GetTargetCharacter();
	ACharacter_TwinBlast* GetTargetPlayer();

private :
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

public :
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private :
	UBlackboardComponent* Blackboard;

};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "BehaviorComponent.generated.h"

class UBlackboardComponent;
class UEnemyStateComponent;
class ACharacter;
class ACharacter_TwinBlast;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBehaviorComponent();

protected:
	virtual void BeginPlay() override;


public:
	FORCEINLINE void SetBlackboard(UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	ACharacter* GetTargetCharacter();
	ACharacter_TwinBlast* GetTargetPlayer();

public :
	UFUNCTION()
		void OnEnemyStateTypeChanged(EEnemyStateType InPrevType, EEnemyStateType InNewType);

private :
	UBlackboardComponent* Blackboard;

private:
	// 블랙보드 키
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";

};

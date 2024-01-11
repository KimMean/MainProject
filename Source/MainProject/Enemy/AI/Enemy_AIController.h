#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class AEnemyBase;

class UBehaviorComponent;

UCLASS()
class MAINPROJECT_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public :
	AEnemy_AIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public :
	FORCEINLINE float GetActionRange() { return ActionRange; }

public :
	float GetSightRadius();
	void SetTargetPlayer(ACharacter* character);

protected :
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private :
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

public :
	void SetSenseConfigSight_SightRadius(float InRadius);
	void SetSenseConfigSight_LoseSightRadius(float InRadius);
	void SetActionRange(float InActionRange);

private:
	UPROPERTY(VisibleDefaultsOnly)
		UBehaviorComponent* Behavior;

private :
	AEnemyBase* OwnerEnemy;
	UAISenseConfig_Sight* Sight;	// ���� Ŭ����

private:
	UPROPERTY(EditAnywhere)
		float ActionRange = 150;	// AI ���� ����
	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true;	// ����� ����
	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50;	// ������ �� ���� ����


};

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class ACorpse_AI;

class UBehaviorComponent;

UCLASS()
class MAINPROJECT_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public :
	AEnemy_AIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private :
	UPROPERTY(EditAnywhere)
		float ActionRange = 150;	// AI ���� ����
	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true;	// ����� ����
	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50;	// ������ �� ���� ����

private :
//	UPROPERTY(VisibleDefaultsOnly)
//		UAIPerceptionComponent* Perception;
	UPROPERTY(VisibleDefaultsOnly)
		UBehaviorComponent* Behavior;

public :
	FORCEINLINE float GetActionRange() { return ActionRange; }

public :
	float GetSightRadius();

protected :
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private :
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

private :
	ACorpse_AI* OwnerEnemy;
	UAISenseConfig_Sight* Sight;	// ���� Ŭ����


};
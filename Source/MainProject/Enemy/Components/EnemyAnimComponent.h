#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "EnemyAnimComponent.generated.h"

class UEnemyAnimDatas;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UEnemyAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyAnimComponent();

protected:
	virtual void BeginPlay() override;

public :
	void Action();
	void Hitted();
	void Stunned();
	void Death();

public :
	void PlayAnimMontage(EEnemyStateType InState);
		
private :
	UPROPERTY(EditDefaultsOnly, Category = "AnimationData")
		UEnemyAnimDatas* AnimDatas;
};

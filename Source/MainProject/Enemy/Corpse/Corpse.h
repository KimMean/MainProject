#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "Corpse.generated.h"

class UEnemyStateComponent;
class UEnemyStatusComponent;
class UEnemyAnimComponent;
class UWidgetComponent;
class AEnemy_Sword;

UCLASS()
class MAINPROJECT_API ACorpse : public ACharacter
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;

public :
	void Death();

public :
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public :
	UFUNCTION()
		void OnEnemyStateTypeChanged(EEnemyStateType InPrevType, EEnemyStateType InNewType);

private :
	void SetDelegates();
	void InitStatus();
	void InitWidgets();
	void EquipmentSword();

private :
	void KnockBack();

private :
	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* NameTagWidget;

	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* HPWidget;

private :
	UPROPERTY(VisibleDefaultsOnly)
		AEnemy_Sword* Sword;

protected :
	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyAnimComponent* Animation;

};

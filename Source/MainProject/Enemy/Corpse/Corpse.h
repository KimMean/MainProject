#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Corpse.generated.h"

class UEnemyStateComponent;
class UEnemyStatusComponent;
class UEnemyAnimComponent;
class UWidgetComponent;

UCLASS()
class MAINPROJECT_API ACorpse : public ACharacter
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;

public :
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private :
	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* HPWidget;

private :
	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyAnimComponent* Animation;

};

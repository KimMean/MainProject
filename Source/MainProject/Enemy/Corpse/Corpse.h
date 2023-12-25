#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Corpse.generated.h"

class UEnemyStateComponent;
class UEnemyStatusComponent;
class UEnemyAnimComponent;

UCLASS()
class MAINPROJECT_API ACorpse : public ACharacter
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		UEnemyAnimComponent* Animation;

};

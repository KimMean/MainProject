#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EEnemySpeedType : uint8
{
	Walk,
	Run,
	Sprint,
	MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINPROJECT_API UEnemyStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyStatusComponent();

protected:
	virtual void BeginPlay() override;

public :
	void SetSpeed(EEnemySpeedType InType);

private :
	UPROPERTY(EditDefaultsOnly)
		float Speed[(int32)EEnemySpeedType::MAX] = { 200, 400, 600 };
		
};

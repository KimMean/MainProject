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
	FORCEINLINE float GetMaxHealthPoint() { return MaxHealthPoint; }
	FORCEINLINE float GetHealthPoint() { return HealthPoint; }
	FORCEINLINE void SetHealthPoint(float InHealthPoint) { HealthPoint = InHealthPoint; }
	void AdjustHealthPoint(float InAdjustValue);

	FORCEINLINE bool GetIsHitted() { return bIsHitted; }
	FORCEINLINE void SetIsHitted(bool InHit) { bIsHitted = InHit; }


public :
	void SetSpeed(EEnemySpeedType InType);


private :
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float Speed[(int32)EEnemySpeedType::MAX] = { 200, 400, 600 };
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Helth")
		float MaxHealthPoint = 100;

private :
	float HealthPoint;
	bool bIsHitted;

};

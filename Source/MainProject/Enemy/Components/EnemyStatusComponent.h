#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatusComponent.generated.h"

class ACharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetChanged, ACharacter*, Target);

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
	FORCEINLINE void SetMaxHealthPoint(float InHealthPoint) { MaxHealthPoint = InHealthPoint; }
	FORCEINLINE void SetHealthPoint(float InHealthPoint) { HealthPoint = InHealthPoint; }
	void AdjustHealthPoint(float InAdjustValue);

	FORCEINLINE bool GetIsHitted() { return bIsHitted; }
	FORCEINLINE void SetIsHitted(bool InHit) { bIsHitted = InHit; }
	FORCEINLINE bool GetIsDead() { return bIsDead; }
	FORCEINLINE void SetIsDead(bool InDead) { bIsDead = InDead; }


public :
	void SetTarget(ACharacter* InCharacter);
	ACharacter* GetTarget();
	void SetSpeed(EEnemySpeedType InType);

private :
	ACharacter* Target;

public :
	FTargetChanged OnTargetChanged;

	UFUNCTION()
		void OnTargetChange(ACharacter* InCharacter);

private :
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float Speed[(int32)EEnemySpeedType::MAX] = { 200, 400, 600 };
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Helth")
		float MaxHealthPoint = 100;

private :
	float HealthPoint;
	bool bIsHitted;
	bool bIsDead;

};

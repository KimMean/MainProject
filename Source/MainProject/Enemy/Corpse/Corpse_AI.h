#pragma once

#include "CoreMinimal.h"
#include "Enemy/Corpse/Corpse.h"
#include "Corpse_AI.generated.h"

class UBehaviorTree;

UCLASS()
class MAINPROJECT_API ACorpse_AI : public ACorpse
{
	GENERATED_BODY()
	
public :
	ACorpse_AI();

	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private :
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

public :
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

};

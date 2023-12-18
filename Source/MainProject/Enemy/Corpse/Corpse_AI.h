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

private :
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

public :
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

};

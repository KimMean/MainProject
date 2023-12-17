#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Corpse.generated.h"

UCLASS()
class MAINPROJECT_API ACorpse : public ACharacter
{
	GENERATED_BODY()

public:
	ACorpse();

protected:
	virtual void BeginPlay() override;


};

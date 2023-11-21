#pragma once

#include "CoreMinimal.h"
#include "Character/DefaultCharacter.h"
#include "Character_TwinBlast.generated.h"

UCLASS()
class MAINPROJECT_API ACharacter_TwinBlast : public ADefaultCharacter
{
	GENERATED_BODY()
	
public :
	ACharacter_TwinBlast();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};

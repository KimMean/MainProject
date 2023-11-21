#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

UCLASS()
class MAINPROJECT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
public :
	AMainHUD();

	virtual void DrawHUD() override;
};

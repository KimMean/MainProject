#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LSA_LobbyLevel.generated.h"

UCLASS()
class MAINPROJECT_API ALSA_LobbyLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public :
	ALSA_LobbyLevel(const FObjectInitializer& ObjectInitializer);
	virtual void PreInitializeComponents() override;
protected:
	virtual void BeginPlay() override;

private :
	class TSubclassOf<class UW_LobbyMain> LobbyWidgetClass;
	class UW_LobbyMain* LobbyWidget;
};

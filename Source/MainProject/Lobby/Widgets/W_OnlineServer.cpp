#include "Lobby/Widgets/W_OnlineServer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UW_OnlineServer::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Connect->OnClicked.AddDynamic(this, &UW_OnlineServer::Btn_Connect_OnClick);
}

void UW_OnlineServer::Btn_Connect_OnClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("127.0.0.1"));
}


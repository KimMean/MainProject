#include "Lobby/Widgets/W_JoinServer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UW_JoinServer::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Connect->OnClicked.AddDynamic(this, &UW_JoinServer::Btn_Connect_OnClick);
}

void UW_JoinServer::Btn_Connect_OnClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("127.0.0.1"));
}

#include "Lobby/Widgets/W_HostServer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UW_HostServer::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Create->OnClicked.AddDynamic(this, &UW_HostServer::Btn_Create_OnClick);
}

void UW_HostServer::Btn_Create_OnClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("TestLevel"), true, ((FString)(L"Listen")));
}


#include "Enemy/Corpse/Corpse.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Components/WidgetComponent.h"
#include "Enemy/Weapons/Enemy_Sword.h"
#include "Enemy/Components/EnemyStateComponent.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/Components/EnemyAnimComponent.h"
#include "Enemy/Widgets/EnemyHelthPoint.h"

#include "Utilities/DebugLog.h"

ACorpse::ACorpse()
{

	State = CreateDefaultSubobject<UEnemyStateComponent>(TEXT("StateComponent"));
	Status = CreateDefaultSubobject<UEnemyStatusComponent>(TEXT("StatusComponent"));
	Animation = CreateDefaultSubobject<UEnemyAnimComponent>(TEXT("AnimationComponent"));

	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HelthWidget"));
	HPWidget->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	ConstructorHelpers::FClassFinder<UEnemyHelthPoint> hpWidget(L"WidgetBlueprint'/Game/Enemies/Widgets/WB_EnemyHelthPoint.WB_EnemyHelthPoint_C'");
	HPWidget->SetWidgetClass(hpWidget.Class);
	HPWidget->SetRelativeLocation(FVector(0, 0, 220));
	HPWidget->SetDrawSize(FVector2D(200, 30));
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();

	AEnemy_Sword* sword = GetWorld()->SpawnActor<AEnemy_Sword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (sword)
	{
		const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName("SwordSocket");
		socket->AttachActor(sword, GetMesh());
	}

	
	HPWidget->InitWidget();
	Status->SetHelthPoint(Status->GetMaxHelthPoint());
	Cast<UEnemyHelthPoint>(HPWidget->GetUserWidgetObject())->Set_HelthPoint_Percent(Status->GetHelthPoint(), Status->GetMaxHelthPoint());
}

float ACorpse::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Cast<UEnemyHelthPoint>(HPWidget->GetUserWidgetObject())->Set_HelthPoint_Percent(50, Status->GetMaxHelthPoint());
	//DebugLog::Print(DamageAmount);

	return DamageAmount;
}


#include "Enemy/AI/Enemy_AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Character/Character_TwinBlast.h"
#include "Enemy/Corpse/Corpse_AI.h"
#include "Enemy/BehaviorComponent.h"

#include "Utilities/DebugLog.h"

AEnemy_AIController::AEnemy_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	Behavior = CreateDefaultSubobject<UBehaviorComponent>(TEXT("Behavior"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 600;	// ���� ����
	Sight->LoseSightRadius = 800;	// ��� ����
	Sight->PeripheralVisionAngleDegrees = 90;	//�þ߰�
	Sight->SetMaxAge(2);	// ����

	// TeamID�� ���� ����
	Sight->DetectionByAffiliation.bDetectEnemies = true;	// ��
	Sight->DetectionByAffiliation.bDetectNeutrals = false;	// �߸�
	Sight->DetectionByAffiliation.bDetectFriendlies = true;	// �Ʊ�

	PerceptionComponent->ConfigureSense(*Sight);	// ����
	PerceptionComponent->SetDominantSense(*Sight->GetSenseImplementation());	// ���� �켱����?

}

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDrawDebug) return;

	FVector center = OwnerEnemy->GetActorLocation();
	center.Z -= AdjustCircleHeight;
	// ���� �׸� ������� ���� �տ��� ���������� �ð����
	DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector); 
	DrawDebugCircle(GetWorld(), center, ActionRange, 300, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);


}

float AEnemy_AIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// ���ǽ�
	OwnerEnemy = Cast<ACorpse_AI>(InPawn);
	SetGenericTeamId(OwnerEnemy->GetTeamID());	// �߸��� 255�� ���� ������ �ִ�. ������ �����鸮

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnPerceptionUpdated);

	// Assets�� Blackboard�� ����
	UBlackboardComponent* blackboardComp = Blackboard;
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, blackboardComp);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void AEnemy_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	// ���ǰ� Ǯ���� ��
	PerceptionComponent->OnPerceptionUpdated.Clear();
}

void AEnemy_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	PerceptionComponent->GetCurrentlyPerceivedActors(nullptr, actors);

	ACharacter_TwinBlast* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACharacter_TwinBlast>(actor);

		if (!!player)
			break;
	}
	Blackboard->SetValueAsObject("Player", player);
}

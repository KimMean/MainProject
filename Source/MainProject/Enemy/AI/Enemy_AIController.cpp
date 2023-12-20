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
	Sight->SightRadius = 600;	// 감지 범위
	Sight->LoseSightRadius = 800;	// 벗어난 범위
	Sight->PeripheralVisionAngleDegrees = 90;	//시야각
	Sight->SetMaxAge(2);	// 유지

	// TeamID에 의해 결정
	Sight->DetectionByAffiliation.bDetectEnemies = true;	// 적
	Sight->DetectionByAffiliation.bDetectNeutrals = false;	// 중립
	Sight->DetectionByAffiliation.bDetectFriendlies = true;	// 아군

	PerceptionComponent->ConfigureSense(*Sight);	// 감지
	PerceptionComponent->SetDominantSense(*Sight->GetSenseImplementation());	// 감지 우선순위?

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
	// 원을 그릴 방향까지 지정 앞에서 오른쪽으로 시계방향
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
	// 빙의시
	OwnerEnemy = Cast<ACorpse_AI>(InPawn);
	SetGenericTeamId(OwnerEnemy->GetTeamID());	// 중립은 255의 값을 가지고 있다. 같으면 프렌들리

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnPerceptionUpdated);

	// Assets에 Blackboard를 적용
	UBlackboardComponent* blackboardComp = Blackboard;
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, blackboardComp);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void AEnemy_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	// 빙의가 풀렸을 때
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

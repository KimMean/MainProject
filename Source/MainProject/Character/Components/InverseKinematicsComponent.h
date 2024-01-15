#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InverseKinematicsComponent.generated.h"

class ACharacter;

USTRUCT(BlueprintType)
struct FIKData
{
	GENERATED_BODY()

		// float형으로 사용해도 되지만 블프에서 작업하기가 귀찮음
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;	// X축만 사용

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;	// X축만 사용

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;	// Z축만 사용

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAINPROJECT_API UInverseKinematicsComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UInverseKinematicsComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// 본이나 소켓을 가져오고 지면에 붙을 간격을 구하는 함수
	void Trace(FName InSocket, float& OutDistance, FRotator& OutRotation);

protected :

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		FName LeftSocket = "foot_l";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		FName RightSocket = "foot_r";
	// 너무 크면 점프할때도 지면에 착 붙는 느낌 ;;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float TraceDistance = 55;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float InterpSpeed = 17;
	// 보정 값
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float OffsetDistance = 5;

public :
	FORCEINLINE const FIKData& GetIKData() { return Data; }

private :
	ACharacter* OwnerCharacter;
	FIKData Data;


};

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

		// float������ ����ص� ������ �������� �۾��ϱⰡ ������
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;	// X�ุ ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;	// X�ุ ���

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;	// Z�ุ ���

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
	// ���̳� ������ �������� ���鿡 ���� ������ ���ϴ� �Լ�
	void Trace(FName InSocket, float& OutDistance, FRotator& OutRotation);

protected :

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		FName LeftSocket = "foot_l";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		FName RightSocket = "foot_r";
	// �ʹ� ũ�� �����Ҷ��� ���鿡 �� �ٴ� ���� ;;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float TraceDistance = 55;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float InterpSpeed = 17;
	// ���� ��
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinematics")
		float OffsetDistance = 5;

public :
	FORCEINLINE const FIKData& GetIKData() { return Data; }

private :
	ACharacter* OwnerCharacter;
	FIKData Data;


};

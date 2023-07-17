// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS/SBTS_BossDamageRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// 这个服务的目的是查询AI与Player之间的距离
void USBTS_BossDamageRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 获取行为树节点的黑板组件
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		// 获取目标对象
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				// 获取AI的对象
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					//bool bWithinRange = DistanceTo < 2000.f;

					//bool bHasLOS = false;
					//if (bWithinRange)
					//{
					//	bHasLOS = MyController->LineOfSightTo(TargetActor);
					//}

					// 不使用硬编码，来设置是否在范围内
					BlackBoardComp->SetValueAsFloat(AttackRangeKey.SelectedKeyName, DistanceTo);
				}

			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ShotProj.generated.h"

/**
 *
 */
UCLASS()
class GAME42_API UBTT_ShotProj : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	// 在这个行为树节点中传入一个子弹类
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> ProjectileClass;

private:

	UPROPERTY(EditAnywhere, Category = "Attack")
		float MaxBulleSpread;

	// 重载执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UBTT_ShotProj();
};
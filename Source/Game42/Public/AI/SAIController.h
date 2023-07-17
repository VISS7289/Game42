// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME42_API ASAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASAIController();

	virtual void OnPossess(APawn* InPawn) override;

protected:
	void BeginPlay() override;

private:
	// 黑板组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
		class UBlackboardComponent* BlackboardComponent;

	// 行为树组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComponent;

	// AI感知组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionComponent* AIPerceptionComponent;

	class ACharacter* EnemyCharacter;
};
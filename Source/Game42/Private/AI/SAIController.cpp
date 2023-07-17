// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASAIController::ASAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void ASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(InPawn))
	{
		return;
	}

	EnemyCharacter = Cast<ACharacter>(InPawn);

	if (!IsValid(EnemyCharacter))
	{
		return;
	}

	if (IsValid(BlackboardComponent->GetBlackboardAsset()))
	{
		BlackboardComponent->InitializeBlackboard(*(BlackboardComponent->GetBlackboardAsset()));
		BehaviorTreeComponent->StartLogic();
	}
}

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	// UGameplayStatics用来获取整个关卡的属性，GetPlayerPawn是获取玩家的函数
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		// 获取黑板元素的值，并设置黑板的MoveToLocation为玩家的位置(只会调用一次)
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

		// 会随着玩家位置的更新重新寻找玩家
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}
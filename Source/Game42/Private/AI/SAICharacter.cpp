// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SAttributeComponent.h"
#include "Component/SActionComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{

	// 添加属性组件
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	// 放置或生成时自动添加AI控制器
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// 监听注意到对象与生命改变
void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::GetHealthChange);
}

// 生命值改变时
// 如果受到攻击，执行材质受击效果，切换攻击目标与死亡判定
void ASAICharacter::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// 受击判断
	if (Delta <= 0.0f)
	{ 
		// 死亡判断
		if (NewHealth <= 0.0f)
		{
			// 停止行为树
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			//// 启用物理模拟（所有关节自由落体并相互之间模拟物理，达成死亡自动倒下的效果）
			//GetMesh()->SetAllBodiesSimulatePhysics(true);
			//GetMesh()->SetCollisionProfileName("Ragdoll");
			// 取消胶囊体碰撞
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			// 10s后销毁自身
			SetLifeSpan(10.0f);
		}
	}
}